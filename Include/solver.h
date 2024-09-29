#ifndef SOLVER_H
#define SOLVER_H

#include "grid.h"

#include <memory>
#include <vector>

class Solver
{
public:
    Solver();

    void solve(std::shared_ptr<Grid> grid);
    void hint(std::shared_ptr<Grid> grid);

private:
bool                try_number();
std::pair<int, int>	find_empty(const Raw_grid & grid);
bool				is_valid(const Raw_grid & grid, int number, std::pair<int, int> & coord);


private:
    bool    do_it(const size_t line, const size_t column) const;
    void    fill_grid(int line, int column, int value) const;

    bool    check_lines(const Raw_grid & grid, const size_t line, const size_t column) const;
    bool    check_line_1st_case(const Raw_grid & grid, const size_t line, const size_t column, const size_t row_of_1st_number) const;
    bool    check_line_2nd_case(const Raw_grid & grid, const size_t line, const size_t column, const size_t row_of_1st_number) const;
    bool    check_line_3rd_case(const Raw_grid & grid, const size_t line, const size_t column, const size_t row_of_1st_number) const;
    int     check_number_in_line(const Raw_grid & grid, const size_t line, const int number) const;
    int     check_full_rows_in_line(const Raw_grid & grid, const size_t line, const int row_of_found_number, const int number_to_check) const;
    bool    try_to_fill_number_in_row_of_line(const Raw_grid & grid,
                                            const size_t line_to_fill,
                                            const int number_to_fill,
                                            const int row_of_1st_number,
                                            const int row_of_2nd_number) const;
    bool    try_to_fill_number_in_1st_row_of_line(const Raw_grid & grid, const size_t line_to_fill, const int number_to_fill) const;
    bool    try_to_fill_number_in_2nd_row_of_line(const Raw_grid & grid, const size_t line_to_fill, const int number_to_fill) const;
    bool    try_to_fill_number_in_3rd_row_of_line(const Raw_grid & grid, const size_t line_to_fill, const int number_to_fill) const;

    bool    check_columns(const Raw_grid & grid, const size_t line, const size_t column) const;
    bool    check_column_1st_case(const Raw_grid & grid, const size_t line, const size_t column, const size_t row_of_1st_number) const;
    bool    check_column_2nd_case(const Raw_grid & grid, const size_t line, const size_t column, const size_t row_of_1st_number) const;
    bool    check_column_3rd_case(const Raw_grid & grid, const size_t line, const size_t column, const size_t row_of_1st_number) const;
    int     check_number_in_column(const Raw_grid & grid, const size_t column, const int number) const;
    int     check_full_rows_in_columns(const Raw_grid & grid, const size_t column, const int row_of_found_number, const int number_to_check) const;
    bool    try_to_fill_number_in_row_of_columns(const Raw_grid & grid,
                                              const size_t column_to_fill,
                                              const int number_to_fill,
                                              const int row_of_1st_number,
                                              const int row_of_2nd_number) const;
    bool    try_to_fill_number_in_1st_row_of_column(const Raw_grid & grid, const size_t column_to_fill, const int number_to_fill) const;
    bool    try_to_fill_number_in_2nd_row_of_column(const Raw_grid & grid, const size_t column_to_fill, const int number_to_fill) const;
    bool    try_to_fill_number_in_3rd_row_of_column(const Raw_grid & grid, const size_t column_to_fill, const int number_to_fill) const;

    bool    try_to_fill_line(const size_t line) const;
    bool    try_to_fill_line_with_2_blank_space(const size_t line,
                                                const std::vector<int> & missing_numbers,
                                                const std::vector<size_t> & blank_columns) const;
    bool    try_to_fill_line_with_more_blank_space(const size_t line,
                                                    const std::vector<int> & missing_numbers,
                                                    const std::vector<size_t> & blank_columns) const;

    bool    try_to_fill_column(const size_t column) const;
    bool    try_to_fill_column_with_2_blank_space(const size_t column,
                                                 const std::vector<int> & missing_numbers,
                                                 const std::vector<size_t> & blank_lines) const;
    bool    try_to_fill_column_with_more_blank_space(const size_t column,
                                                    const std::vector<int> & missing_numbers,
                                                    const std::vector<size_t> & blank_lines) const;


private:
    std::shared_ptr<Grid> m_grid;
};

#endif // SOLVER_H
