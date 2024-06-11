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
Grid::get_grid() const {
    return m_raw_grid;
}

const std::pair<int, int> &
Grid::get_filled_cell() const {
    return m_filled_cell;
}

void
Grid::set_filled_cell(const std::pair<int, int> & cell) {
    m_filled_cell = cell;
}

void
Grid::set_value_in_cell(const int line, const int column, const int value)
{
    m_raw_grid[line][column] = value;
}

bool
Grid::is_number_in_cell(const int line, const int column, const int value) const
{
    if (m_raw_grid[line][column] == value)
        return true;

    return false;
}


bool
Grid::is_number_in_column(const int column, const int number) const
{
    for (int line_check = 0; line_check < 9; ++line_check)
    {
        if (m_raw_grid[line_check][column] == number)
            return true;
    }
    return false;
}

bool
Grid::is_number_in_line(const int line, const int number) const
{
    for (int column_check = 0; column_check < 9; ++column_check)
    {
        if (m_raw_grid[line][column_check] == number)
            return true;
    }
    return false;
}
