#include "Map.h"
#include <fstream>      
#include <stdexcept>    

void Map::loadFromFile(const std::string& path)
{
    // מנסים לפתוח את הקובץ — אם לא קיים, הפתיחה נכשלת בשקט (ifstream)
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Map::loadFromFile - cannot open: " + path);

    // קוראים את כל הקובץ שורה שורה לתוך וקטור של מחרוזות
    // כך אפשר לדעת את גודל המפה לפני שבונים את הגריד (vector<string>)
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line))
    {
        if (!line.empty())      // מדלגים על שורות ריקות — לא יוצרים תאים מיותרים
            lines.push_back(line);
    }

    if (lines.empty())
        throw std::runtime_error("Map::loadFromFile - file is empty: " + path);

    // מחשבים את גודל המפה מתוכן הקובץ
    // ממירים ל-int כי size() מחזיר ערך חיובי-בלבד שעלול לגרום לבעיות בהשוואות (static_cast)
    int rows = static_cast<int>(lines.size());
    int cols = static_cast<int>(lines[0].size());

    // מחליפים את הגריד הזמני בגריד האמיתי בגודל הנכון
    // כל התאים מאותחלים לרצפה אוטומטית כברירת מחדל (Grid<Tile>)
    m_grid = Grid<Tile>(rows, cols);

    // מנקים נקודות עצירה ישנות — חשוב אם הפונקציה נקראת פעם שנייה על מפה אחרת
    m_checkpoints.clear();

    // עוברים על כל תו בקובץ וממירים אותו לסוג תא
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < static_cast<int>(lines[r].size()); ++c)
        {
            TileType type = TileType::FLOOR; // ברירת מחדל — אם התו לא מוכר

            switch (lines[r][c])
            {
            case '#': type = TileType::WALL;        break; // קיר
            case 'O': type = TileType::BOULDER;     break; // אבן נופלת
            case 'D': type = TileType::DIAMOND;     break; // יהלום לאיסוף
            case 'E': type = TileType::DOOR;        break; // דלת יציאה

            case 'C':
                type = TileType::CHECKPOINT;
                m_checkpoints.push_back({ r, c }); // שומרים את המיקום — השחקן יחזור לכאן אחרי מוות
                break;

            case 'B': type = TileType::BUTTON;      break; // כפתור

            case 'P':
                type = TileType::FLOOR;             // התא עצמו הוא רצפה רגילה
                m_playerStart = { r, c };           // שומרים את נקודת ההתחלה של השחקן
                break;

            default:  type = TileType::FLOOR;       break; // תו לא מוכר ? רצפה
            }

            // יוצרים תא עם הסוג הנכון — הבנאי מגדיר את הצבע אוטומטית (Tile)
            m_grid.set(r, c, Tile(type));
        }
    }
}

// מחזירים גישה ישירה לתא — אפשר לשנות אותו (getTile)
Tile& Map::getTile(int row, int col)
{
    return m_grid.get(row, col);
}

// מחזירים גישה לתא לקריאה בלבד — נקראת כשהמפה מגיעה לפונקציה שלא אמורה לשנות אותה (const getTile)
const Tile& Map::getTile(int row, int col) const
{
    return m_grid.get(row, col);
}

// משנים את סוג התא — הגישה מחזירה הפניה ישירה לתא, אז השינוי פועל על המקור (setTile)
void Map::setTile(int row, int col, TileType type)
{
    m_grid.get(row, col).setType(type);
}

// מחזירים את גודל המפה — מועבר ישירות מהגריד הפנימי
int Map::getRows() const { return m_grid.getRows(); }
int Map::getCols() const { return m_grid.getCols(); }

// מחזירים עותקים — שני הערכים קטנים, אין סיבה לחשוף הפניה לפנים
Position Map::getPlayerStart() const { return m_playerStart; }
std::vector<Position> Map::getCheckpoints() const { return m_checkpoints; }