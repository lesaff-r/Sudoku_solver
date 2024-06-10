#ifndef SOLVER_H
#define SOLVER_H

#include "grid.h"
#include "qtmetamacros.h"

#include <functional>
#include <memory>

class Solver
{
public:
    Solver();

    void hint(std::shared_ptr<Grid> grid);

private:
    bool    do_it(const size_t & line, const size_t & column);
    void    fill_grid(int line, int column, int value);

    bool    check_lines(const Raw_grid & grid, const size_t & line, const size_t & column);
    bool    check_line_1st_case(const Raw_grid & grid, const size_t & line, const size_t & column, const size_t & row_of_cells);
    bool    check_line_2nd_case(const Raw_grid & grid, const size_t & line, const size_t & column, const size_t & row_of_cells);
    bool    check_line_3rd_case(const Raw_grid & grid, const size_t & line, const size_t & column, const size_t & row_of_cells);
    int     check_number_in_line(const Raw_grid & grid, const size_t & line, const int number);
    int     check_full_rows_in_line(const Raw_grid & grid, const size_t & line, const int row_of_found_number, const int number_to_check);
    bool    try_to_fill_number_in_row_of_line(const Raw_grid & grid,
                                            const size_t line_to_fill,
                                            const int number_to_fill,
                                            const int row_of_cells,
                                            const int row);
    bool    try_to_fill_number_in_1st_row_of_line(const Raw_grid & grid, const size_t line_to_fill, const int number_to_fill);
    bool    try_to_fill_number_in_2nd_row_of_line(const Raw_grid & grid, const size_t line_to_fill, const int number_to_fill);
    bool    try_to_fill_number_in_3rd_row_of_line(const Raw_grid & grid, const size_t line_to_fill, const int number_to_fill);

    bool    check_columns(const Raw_grid & grid, const size_t & line, const size_t & column);

private:
    std::shared_ptr<Grid> m_grid;
};

#endif // SOLVER_H
