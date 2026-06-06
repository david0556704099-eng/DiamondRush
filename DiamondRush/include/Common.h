#pragma once

// אחראי על הגדרת מבני נתונים בסיסיים כמו מיקום וכיוון, שישמשו במשחק.
struct Position
{
    int row;
    int col;
};

// כיוון התנועה של השחקן או האובייקטים במשחק.
enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};