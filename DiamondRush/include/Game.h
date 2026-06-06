#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "PhysicsEngine.h"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents(); //תהליך אירועים-מטפל בקלט
    void update(float deltaTime); //עדכון-מקבל זמן שעבר מהפריים האחרון
    void render(); //מצייר את המפה

    sf::RenderWindow m_window;//החלון הגרפי.
    Map m_map;                //מפה
    PhysicsEngine m_physics;  //מנוע הפיזיקה
};