#pragma once
#include <vector>
#include <stdexcept>

// טבלה דו-ממדית גנרית — עובדת עם כל T
// Grid<Tile> למפה, Grid<int> ל-BFS
template<typename T>
class Grid
{
public:

    // T{} = ערך ברירת מחדל של T: int?0, bool?false, Tile?FLOOR
    Grid(int rows = 1, int cols = 1, T defaultValue = T{})
        : m_rows(rows), m_cols(cols),
        m_data(rows, std::vector<T>(cols, defaultValue))
    {
    }

    // מחזיר reference — אפשר לשנות 
    T& get(int row, int col)
    {
        if (row < 0 || row >= m_rows || col < 0 || col >= m_cols)
            throw std::out_of_range("Grid::get - out of range");
        return m_data[row][col];
    }

    //  לקריאה בלבד -Grid מגיע כ-const&
    const T& get(int row, int col) const
    {
        if (row < 0 || row >= m_rows || col < 0 || col >= m_cols)
            throw std::out_of_range("Grid::get - out of range");
        return m_data[row][col];
    }

    // move במקום copy — val כבר הועתק בכניסה, אין טעם להעתיק שוב
    void set(int row, int col, T val)
    {
        if (row < 0 || row >= m_rows || col < 0 || col >= m_cols)
            throw std::out_of_range("Grid::set - out of range");
        m_data[row][col] = std::move(val);
    }

    int getRows() const { return m_rows; }
    int getCols() const { return m_cols; }

    // ??? Iterator ????????????????????????????????????????????????????????????
    // מאפשר: for (auto& tile : grid) { ... }
    class Iterator
    {
    public:
        // מקבל reference לטבלה המקורית  + מיקום התחלתי
        Iterator(std::vector<std::vector<T>>& data, int row, int col, int cols)
            : m_data(data), m_row(row), m_col(col), m_cols(cols)
        {
        }

        T& operator*()  // *it ? התא הנוכחי
        {
            return m_data[m_row][m_col];
        }

        Iterator& operator++()  // ++it ? זוז קדימה (row-major: שמאל?ימין?שורה הבאה)
        {
            ++m_col;
            if (m_col >= m_cols)
            {
                m_col = 0;
                ++m_row;
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const  // תנאי העצירה של הלולאה
        {
            return m_row != other.m_row || m_col != other.m_col;
        }

    private:
        std::vector<std::vector<T>>& m_data; // reference לטבלה  
        int m_row; //מיקום שורה נוכחי
        int m_col; //מיקום עמודה נוכחי
        int m_cols; // נחוץ כדי לדעת מתי לעבור שורה
    };

    Iterator begin() { return Iterator(m_data, 0, 0, m_cols); } // תא ראשון (0,0)
    Iterator end() { return Iterator(m_data, m_rows, 0, m_cols); } // אחרי התא האחרון — תנאי עצירה

private:
    int m_rows;//מספר השורות
    int m_cols;//מספר העמודות
    std::vector<std::vector<T>> m_data; // הטבלה עצמה — vector של שורות, כל שורה vector של T
};