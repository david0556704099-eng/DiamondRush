#include "Tile.h"

// מאתחל את הסוג ואת הצורה הגרפית בגודל 32x32 פיקסלים
// updateColor נקראת מיד — מבטיחה שהצבע מסונכרן עם הסוג מהרגע הראשון
Tile::Tile(TileType type)
    : m_type(type), m_shape(sf::Vector2f(32.f, 32.f))
{
    updateColor();
}

// שאלת כן/לא — האם ניתן להיכנס לתא
// fall-through מכוון: כמה סוגים שתשובתם זהה מגיעים לאותו return
bool Tile::isPassable() const
{
    switch (m_type)
    {
    case TileType::FLOOR:
    case TileType::DIAMOND:
    case TileType::DOOR:
    case TileType::CHECKPOINT:
    case TileType::BUTTON:
        return true;        // ניתן להיכנס — משהו יקרה בכניסה אבל לא נחסמים

    case TileType::WALL:
    case TileType::BOULDER:
        return false;       // חוסמים מעבר לחלוטין
    }

    return false;           // הגנה — מגיעים לכאן רק אם נוסף סוג חדש ושכחו לעדכן
}

// מחזיר עותק של הסוג — זול כי הסוג הוא סתם מספר שלם מתחת למכסה
TileType Tile::getType() const
{
    return m_type;
}

// משנה סוג וצבע יחד — לעולם לא משנים אחד בלי השני
void Tile::setType(TileType type)
{
    m_type = type;
    updateColor();  // invariant: m_type ו-m_shape תמיד מסונכרנים
}

// מחזיר עותק של הצורה — render ישנה את המיקום על העותק, לא על המקור
sf::RectangleShape Tile::getShape() const
{
    return m_shape;
}

// מסנכרנת את צבע הצורה לסוג הנוכחי
// נקראת רק מהבנאי ומ-setType — לכן private
void Tile::updateColor()
{
    switch (m_type)
    {
    case TileType::FLOOR:
        m_shape.setFillColor(sf::Color(30, 30, 30));      // כמעט שחור — רקע כהה
        break;
    case TileType::WALL:
        m_shape.setFillColor(sf::Color(180, 180, 180));   // אפור בהיר
        break;
    case TileType::BOULDER:
        m_shape.setFillColor(sf::Color(139, 69, 19));     // חום אדמה — saddle brown
        break;
    case TileType::DIAMOND:
        m_shape.setFillColor(sf::Color::Cyan);            // תכלת — בולט על הרקע הכהה
        break;
    case TileType::DOOR:
        m_shape.setFillColor(sf::Color::Green);           // ירוק — יציאה
        break;
    case TileType::CHECKPOINT:
        m_shape.setFillColor(sf::Color::Yellow);          // צהוב — נקודת שמירה
        break;
    case TileType::BUTTON:
        m_shape.setFillColor(sf::Color::Magenta);         // סגול — כפתור
        break;
    }
}