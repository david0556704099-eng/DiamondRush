#include "PhysicsEngine.h"

// שומר את המצביע למפה — לא מעתיק, לא מוחק
PhysicsEngine::PhysicsEngine(Map* map)
    : m_map(map)
{
}

void PhysicsEngine::update(float deltaTime)
{
    // צוברים זמן — הפיזיקה לא רצה כל פריים אלא כל STEP שניות
    // כך נפילת האבנות נראית איטית ומובחנת, לא מיידית
    m_accumulator += deltaTime;

    // לולאה במקרה שצעדים מרובים "נשארו חוב" — למשל אם פריים אחד לקח זמן רב
    while (m_accumulator >= STEP)
    {
        m_accumulator -= STEP;

        int rows = m_map->getRows();
        int cols = m_map->getCols();

        // עוברים מלמטה למעלה — קריטי לפיזיקה נכונה
        // אם היינו עוברים מלמעלה למטה, אבן שנפלה בצעד זה היתה מיד מטופלת שוב
        // ותנפול כמה תאים בצעד אחד במקום אחד
        // rows-2 כי השורה האחרונה (rows-1) אין מתחתיה כלום — אבן שם לא יכולה ליפול
        for (int r = rows - 2; r >= 0; --r)
        {
            for (int c = 0; c < cols; ++c)
            {
                // בודקים רק תאי אבן
                if (m_map->getTile(r, c).getType() == TileType::BOULDER)
                {
                    // אבן נופלת רק אם התא ישירות מתחתיה פנוי
                    if (m_map->getTile(r + 1, c).getType() == TileType::FLOOR)
                    {
                        m_map->setTile(r, c, TileType::FLOOR);   // התא הנוכחי מתרוקן
                        m_map->setTile(r + 1, c, TileType::BOULDER); // האבן זזה תא אחד מטה
                    }
                }
            }
        }
    }
}