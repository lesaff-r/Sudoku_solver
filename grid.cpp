#include "grid.h"

Grid::Grid() {
    Init_grid();
}

void
Grid::Init_grid()
{
    m_raw_grid = {
        { 0,0,0, 2,0,0, 3,0,0 },
        { 0,0,0, 3,0,0, 0,5,7 },
        { 0,9,8, 5,0,0, 0,0,0 },

        { 0,3,0, 0,6,0, 4,0,5 },
        { 8,0,0, 0,0,0, 0,0,6 },
        { 6,0,2, 0,1,0, 0,7,0 },

        { 0,0,0, 0,0,5, 9,1,0 },
        { 5,1,0, 0,0,9, 0,0,0 },
        { 0,0,3, 0,0,4, 0,0,0 }
    };
}

const Raw_grid &
Grid::get_grid() {
    return m_raw_grid;
}

void
Grid::set_value_in_cell(const int line, const int column, const int value)
{
    m_raw_grid[line][column] = value;
}

bool
Grid::Is_number_in_cell(const int line, const int column, const int value)
{
    if (m_raw_grid[line][column] == value)
        return true;

    return false;
}
