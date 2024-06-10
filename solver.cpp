#include "solver.h"
#include "qdebug.h"

Solver::Solver()
{}


void
Solver::hint(std::shared_ptr<Grid> grid)
{
    m_grid = std::move(grid);

    for (size_t line_check = 0 ; line_check < 9 ; ++line_check)
    {
        for (size_t column_check = 0 ; column_check < 9 ; ++column_check)
        {
            do_it(line_check, column_check);
        }
    }
}

bool
Solver::do_it(const size_t & line, const size_t & column)
{
    const Raw_grid & grid = m_grid->get_grid();

    if (grid[line][column] != 0)
    {
        qDebug() << "CHECKING [" << line << "][" << column << "] : " << grid[line][column];
        if (check_lines(grid, line, column) ||
            check_columns(grid, line, column))
            return true;
    }
    /*else
    {
        if (can_fill_line(grid, line) ||
            can_fill_column(grid, column))
            return true;
    }*/
    return false;
}

void
Solver::fill_grid(int line, int column, int value)
{
    m_grid->set_value_in_cell(line, column, value);
    m_grid->set_filled_cell({line, column});
}

bool
Solver::check_lines(const Raw_grid & grid, const size_t & line, const size_t & column)
{
    const size_t LINE = (line + 1) % 3;
    size_t row_of_1st_number = column / 3 + 1;

    // First case
    // LINE Number found
    // LINE To check
    // LINE To check
    if (LINE == 1)
        return check_line_1st_case(grid, line, column, row_of_1st_number);

    // Second case
    // LINE To check
    // LINE Number found
    // LINE To check
    else if (LINE == 2)
        return check_line_2nd_case(grid, line, column, row_of_1st_number);

    // Third case
    // LINE To check
    // LINE To check
    // LINE Number found
    else if (LINE == 0)
        return check_line_3rd_case(grid, line, column, row_of_1st_number);

    else // Should never go here
        qDebug() << "What am I doing here ?!" << " LINE is " << LINE;

    return false;
}

bool
Solver::check_line_1st_case(const Raw_grid & grid, const size_t & line, const size_t & column, const size_t & row_of_1st_number)
{
    //qDebug() << "In LINE Case 1";

    // Checking for the number in other lines
    if (int row_of_2nd_number = check_number_in_line(grid, line + 1, grid[line][column]))
        return try_to_fill_number_in_row_of_line(grid, line + 2, grid[line][column], row_of_1st_number, row_of_2nd_number);

    if (int row_of_2nd_number = check_number_in_line(grid, line + 2, grid[line][column]))
        return try_to_fill_number_in_row_of_line(grid, line + 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    // Checking for full rows in other lines
    if (int row_of_2nd_number = check_full_rows_in_line(grid, line + 1, row_of_1st_number, grid[line][column]))
        return try_to_fill_number_in_row_of_line(grid, line + 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    if (int row_of_2nd_number = check_full_rows_in_line(grid, line + 2, row_of_1st_number, grid[line][column]))
        return try_to_fill_number_in_row_of_line(grid, line + 2, grid[line][column], row_of_1st_number, row_of_2nd_number);

    //qDebug() << "Number " << grid[line][column] << " not found on other lines";
    return false;
}

bool
Solver::check_line_2nd_case(const Raw_grid & grid, const size_t & line, const size_t & column, const size_t & row_of_1st_number)
{
    // qDebug() << "In LINE Case 2";

    // Checking for the number in other lines
    if (int row_of_2nd_number = check_number_in_line(grid, line - 1, grid[line][column]))
        return try_to_fill_number_in_row_of_line(grid, line + 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    if (int row_of_2nd_number = check_number_in_line(grid, line + 1, grid[line][column]))
        return try_to_fill_number_in_row_of_line(grid, line - 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    // Checking for full rows in other lines
    if (int row_of_2nd_number = check_full_rows_in_line(grid, line - 1, row_of_1st_number, grid[line][column]))
        return try_to_fill_number_in_row_of_line(grid, line - 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    if (int row_of_2nd_number = check_full_rows_in_line(grid, line + 1, row_of_1st_number, grid[line][column]))
        return try_to_fill_number_in_row_of_line(grid, line + 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    //qDebug() << "Number " << grid[line][column] << " not found on other lines";
    return false;
}

bool
Solver::check_line_3rd_case(const Raw_grid & grid, const size_t & line, const size_t & column, const size_t & row_of_1st_number)
{
    //qDebug() << "In LINE Case 3" << std::endl;

    // Checking for the number in other lines
    if (int row_of_2nd_number = check_number_in_line(grid, line - 1, grid[line][column]))
        return try_to_fill_number_in_row_of_line(grid, line - 2, grid[line][column], row_of_1st_number, row_of_2nd_number);

    if (int row_of_2nd_number = check_number_in_line(grid, line - 2, grid[line][column]))
        return try_to_fill_number_in_row_of_line(grid, line - 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    // Checking for full rows in other lines
    if (int row_of_2nd_number = check_full_rows_in_line(grid, line - 1, row_of_1st_number, grid[line][column]))
        return try_to_fill_number_in_row_of_line(grid, line - 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    if (int row_of_2nd_number = check_full_rows_in_line(grid, line - 2, row_of_1st_number, grid[line][column]))
        return try_to_fill_number_in_row_of_line(grid, line - 2, grid[line][column], row_of_1st_number, row_of_2nd_number);

    //qDebug() << "Number " << grid[line][column] << " not found on other lines";
    return false;
}

int
Solver::check_number_in_line(const Raw_grid & grid, const size_t & line, const int number)
{
    for (size_t column_check = 0; column_check < 9; ++column_check)
    {
        if (grid[line][column_check] == number)
            return (column_check / 3 + 1);
    }
    return 0;
}

int
Solver::check_full_rows_in_line(const Raw_grid & grid, const size_t & line, const int row_of_found_number, const int number_to_check)
{
    int numbers_in_row = 0;

    for (size_t column_check = 0; column_check < 9; ++column_check)
    {
        if (grid[line][column_check] ||
            m_grid->is_number_in_column(column_check, number_to_check))
            numbers_in_row++;

        if ((column_check + 1) % 3 == 0)
        {
            if (numbers_in_row == 3 &&
                row_of_found_number != column_check / 3 + 1)
                return (column_check / 3 + 1);  // Number not found but the row is already full or can not be filled with it
            else
                numbers_in_row = 0;
        }
    }
    return 0;
}

bool
Solver::try_to_fill_number_in_row_of_line(const Raw_grid & grid,
                                        const size_t line_to_fill,
                                        const int number_to_fill,
                                        const int row_of_1st_number,
                                        const int row_of_2nd_number)
{
    if (row_of_1st_number == 1)             // The First number is in the 1st rows of 3 cells (|X|X|X|3|4|5|6|7|8|)
    {
        if (row_of_2nd_number == 2)         // The Second number is in the 2nd rows (|0|1|2|X|X|X|6|7|8|)
            return try_to_fill_number_in_3rd_row_of_line(grid, line_to_fill, number_to_fill);
        else if (row_of_2nd_number == 3)    // The Second number is in the 3rd rows (|0|1|2|3|4|5|X|X|X|)
            return try_to_fill_number_in_2nd_row_of_line(grid, line_to_fill, number_to_fill);
        else // Should never go here
            qDebug() << "/!\\ Same rows ?!" << " 1st_row is " << row_of_1st_number << " & 2nd_row is " << row_of_2nd_number;
    }

    else if (row_of_1st_number == 2)
    {
        if (row_of_2nd_number == 1)
            return try_to_fill_number_in_3rd_row_of_line(grid, line_to_fill, number_to_fill);
        else if (row_of_2nd_number == 3)
            return try_to_fill_number_in_1st_row_of_line(grid, line_to_fill, number_to_fill);
        else // Should never go here
            qDebug() << "/!\\ Same rows ?!" << " 1st_row is " << row_of_1st_number << " & 2nd_row is " << row_of_2nd_number;
    }

    else if (row_of_1st_number == 3)
    {
        if (row_of_2nd_number == 1)
            return try_to_fill_number_in_2nd_row_of_line(grid, line_to_fill, number_to_fill);
        else if (row_of_2nd_number == 2)
            return try_to_fill_number_in_1st_row_of_line(grid, line_to_fill, number_to_fill);
        else // Should never go here
            qDebug() << "/!\\ Same rows ?!" << " 1st_row is " << row_of_1st_number << " & 2nd_row is " << row_of_2nd_number;
    }

    else    // Should never go here
        qDebug() << "What am I doing here ?!" << " 1st_row is " << row_of_1st_number;

    return false;
}

// We are then trying to fill here |X|X|X|3|4|5|6|7|8|
bool
Solver::try_to_fill_number_in_1st_row_of_line(const Raw_grid & grid, const size_t line_to_fill, const int number_to_fill)
{
    bool has_number = false;
    int number_of_blank = 0;
    size_t cell_to_fill = 0;

    for (size_t cell = 0; cell < 3; cell++)
    {
        if (grid[line_to_fill][cell] == 0)
        {
            // Checking the column to see if it has number_to_fill
            if (!m_grid->is_number_in_column(cell, number_to_fill))
            {
                number_of_blank++;
                cell_to_fill = cell;
            }
        }
        else if (grid[line_to_fill][cell] == number_to_fill)
            has_number = true;
    }

    if (!has_number && number_of_blank == 1)
    {
        // Finally filling the grid
        fill_grid(line_to_fill, cell_to_fill, number_to_fill);

        return true;
    }

    /*qDebug() << "Could not fill 1st row of line with " << number_to_fill << " -> ";
    if (has_number)
        qDebug() << "already there";
    else
        qDebug() << "too many possibilities";*/

    return false;
}

// We are then trying to fill here |0|1|2|X|X|X|6|7|8|
bool
Solver::try_to_fill_number_in_2nd_row_of_line(const Raw_grid & grid, const size_t line_to_fill, const int number_to_fill)
{
    bool has_number = false;
    int number_of_blank = 0;
    size_t cell_to_fill = 0;

    for (size_t cell = 3; cell < 6; cell++)
    {
        if (grid[line_to_fill][cell] == 0)
        {
            // Checking the column to see if it has number_to_fill
            if (!m_grid->is_number_in_column(cell, number_to_fill))
            {
                number_of_blank++;
                cell_to_fill = cell;
            }
        }
        else if (grid[line_to_fill][cell] == number_to_fill)
            has_number = true;
    }

    if (!has_number && number_of_blank == 1)
    {
        // Finally filling the grid
        fill_grid(line_to_fill, cell_to_fill, number_to_fill);

        return true;
    }

    /*qDebug() << "Could not fill 2nd row of line with " << number_to_fill << " -> ";
    if (has_number)
        std::cout << "already there" << std::endl;
    else
        std::cout << "too many possibilities" << std::endl;*/

    return false;
}

// We are then trying to fill here |0|1|2|3|4|5|X|X|X|
bool
Solver::try_to_fill_number_in_3rd_row_of_line(const Raw_grid & grid, const size_t line_to_fill, const int number_to_fill)
{
    bool has_number = false;
    int number_of_blank = 0;
    size_t cell_to_fill = 0;

    for (size_t cell = 6; cell < 9; cell++)
    {
        if (grid[line_to_fill][cell] == 0)
        {
            // Checking the column to see if it has number_to_fill
            if (!m_grid->is_number_in_column(cell, number_to_fill))
            {
                number_of_blank++;
                cell_to_fill = cell;
            }
        }
        else if (grid[line_to_fill][cell] == number_to_fill)
            has_number = true;
    }

    if (!has_number && number_of_blank == 1)
    {
        // Finally filling the grid
        fill_grid(line_to_fill, cell_to_fill, number_to_fill);

        return true;
    }

    /*qDebug() << "Could not fill 2nd row of line with " << number_to_fill << " -> ";
    if (has_number)
        std::cout << "already there" << std::endl;
    else
        std::cout << "too many possibilities" << std::endl;*/

    return false;
}


bool
Solver::check_columns(const Raw_grid & grid, const size_t & line, const size_t & column)
{
    return false;
}
