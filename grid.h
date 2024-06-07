#ifndef GRID_H
#define GRID_H

#include <vector>

using Raw_grid = std::vector<std::vector<int>>;

class Grid
{
public:
    Grid();

    const Raw_grid &    get_grid();

    void    set_value_in_cell(const int line, const int column, const int value);
    bool    Is_number_in_square(const int line, const int column, const int value);
    bool    Is_number_in_cell(const int line, const int column, const int value);


private:
    void Init_grid();


private:
    Raw_grid  m_raw_grid;
};

#endif // GRID_H
