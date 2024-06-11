#ifndef GRID_H
#define GRID_H

#include <vector>

using Raw_grid = std::vector<std::vector<int>>;

class Grid
{
public:
    Grid();

    const Raw_grid &    get_grid() const;

    const std::pair<int, int> & get_filled_cell() const;
    void                        set_filled_cell(const std::pair<int, int> & cell);

    void    set_value_in_cell(const int line, const int column, const int value);
    bool    is_number_in_cell(const int line, const int column, const int value) const;

    bool    is_number_in_column(const int column, const int number) const;
    bool    is_number_in_line(const int line, const int number) const;

public:
    const std::vector<int> & operator[](const int value) {return m_raw_grid[value];}

private:
    void Init_grid();

private:
    Raw_grid  m_raw_grid;

    std::pair<int,int> m_filled_cell;
};

#endif // GRID_H
