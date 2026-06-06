#pragma once
#include <SFML/Graphics.hpp>    // צורה גרפית לכל תא (RectangleShape)

// סוגי התאים האפשריים במפה
// enum class = כל ערך חייב להיכתב עם שם המחלקה לפניו — מונע התנגשות שמות (TileType::FLOOR)
enum class TileType
{
    FLOOR,       // רצפה — ניתן למעבר
    WALL,        // קיר — חוסם מעבר
    BOULDER,     // אבן נופלת — חוסמת מעבר, מזיקה אם נופלת על שחקן
    DIAMOND,     // יהלום לאיסוף — ניתן למעבר
    DOOR,        // דלת יציאה — ניתן למעבר
    CHECKPOINT,  // נקודת שמירה — ניתן למעבר
    BUTTON       // כפתור — ניתן למעבר
};

// תא בודד במפה — יודע מה הוא ואיך הוא נראה
// הקשר בין הסוג לצבע נשמר תמיד מסונכרן — שינוי סוג מעדכן צבע אוטומטית
class Tile
{
public:

    // explicit — מונע יצירת תא בטעות מהמרה אוטומטית של TileType
    // ברירת מחדל היא רצפה — מאפשר יצירת תא ריק ללא פרמטרים (Grid צריך את זה)
    explicit Tile(TileType type = TileType::FLOOR);

    // האם ניתן להיכנס לתא — שאלת כן/לא, לא בודק אם ריק (isPassable)
    // DIAMOND, DOOR, CHECKPOINT, BUTTON — כולם ניתנים למעבר כי הדמות נכנסת ומשהו קורה
    bool isPassable() const;

    // מחזיר את הסוג הנוכחי של התא
    TileType getType() const;

    // משנה את הסוג ומעדכן את הצבע אוטומטית — שני הנתונים תמיד מסונכרנים
    void setType(TileType type);

    // מחזיר עותק של הצורה — כי render צריך לשנות את המיקום לפני ציור, בלי לפגוע במקור
    sf::RectangleShape getShape() const;

private:

    TileType m_type;            // הסוג הנוכחי — קובע התנהגות (passable, פיזיקה)
    sf::RectangleShape m_shape; // הצורה הגרפית — צבע מתעדכן בכל שינוי סוג

    // מסנכרן את צבע הצורה לסוג הנוכחי — נקראת רק מהבנאי ומ-setType
    void updateColor();
};