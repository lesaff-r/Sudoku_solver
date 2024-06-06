#ifndef GRID_H
#define GRID_H

#include <vector>

using Raw_grid = std::vector<std::vector<int>>;

class Grid
{
public:
    Grid();

    const Raw_grid & get_grid();

private:
    void Init_grid();


private:
    Raw_grid  m_raw_grid;
};

#endif // GRID_H
