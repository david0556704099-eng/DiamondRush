#pragma once
#include <string>       
#include <vector>       
#include "Grid.h"       
#include "Tile.h"       
#include "Common.h"     

// מייצגת מפה טעונה מקובץ טקסט
// מחזיקה Grid<Tile> בתוכה, ומספקת ממשק נוח מעליו
class Map
{
public:

    // טוענת מפה מקובץ טקסט — זורקת std::runtime_error אם הקובץ לא נמצא
    void loadFromFile(const std::string& path);

    // גישה לתא בודד — non-const לשינוי, const לקריאה בלבד
    Tile& getTile(int row, int col);
    const Tile& getTile(int row, int col) const;

    // משנה את סוג תא ספציפי — מעדכן גם את הצבע אוטומטית (דרך Tile::setType)
    void setTile(int row, int col, TileType type);

    // גודל המפה — מועבר ישירות מה-Grid
    int getRows() const;
    int getCols() const;

    // מיקום התחלתי של השחקן — נקרא פעם אחת בטעינת המפה
    Position getPlayerStart() const;

    // רשימת כל נקודות ה-Checkpoint במפה — נשמרות בטעינה
    std::vector<Position> getCheckpoints() const;

private:

    Grid<Tile> m_grid{ 1, 1 };          // הטבלה עצמה — מאותחלת ל-1×1 עד שתיטען מפה
    Position m_playerStart{ 0, 0 };     // מיקום ה-'P' שנמצא בקובץ הטקסט
    std::vector<Position> m_checkpoints;// כל ה-'C' שנמצאו בקובץ — לפי סדר הטעינה
};