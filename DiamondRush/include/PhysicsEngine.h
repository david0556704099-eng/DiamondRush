#pragma once
#include <SFML/Graphics.hpp>    
#include "Map.h"                

// מטפל בפיזיקת האבנים — נפילה כלפי מטה כשהתא מתחתיהן פנוי
// מחזיק רק מצביע למפה — לא הבעלים שלה, רק ניגש אליה (Map*)
class PhysicsEngine
{
public:

    // מקבל מצביע למפה — raw pointer כי PhysicsEngine לא אחראי על חיי המפה
    explicit PhysicsEngine(Map* map);

    // נקרא כל פריים — מצבר זמן ומפעיל צעד פיזיקה כל STEP שניות
    void update(float deltaTime);

private:

    Map* m_map;                         // גישה למפה — לא בעלות

    float m_accumulator = 0.f;          // זמן שהצטבר מאז הצעד האחרון

    // הזמן בשניות בין כל נפילת אבן — constexpr נקבע בזמן קומפילציה, לא תופס זיכרון
    static constexpr float STEP = 0.3f;
};