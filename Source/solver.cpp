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
            if (do_it(line_check, column_check))
                return;
        }
    }

    qDebug() << "Solver could not find a solution OR the Grid is full";
}

bool
Solver::do_it(const size_t & line, const size_t & column) const
{
    const Raw_grid & grid = m_grid->get_grid();

    if (grid[line][column] != 0)
    {
        //qDebug() << "CHECKING [" << line << "][" << column << "] : " << grid[line][column];
        if (check_lines(grid, line, column) ||
            check_columns(grid, line, column))
            return true;
    }
    else
    {
        if (try_to_fill_line(line) ||
            try_to_fill_column(column))
            return true;
    }
    return false;
}

void
Solver::fill_grid(int line, int column, int value) const
{
    m_grid->set_value_in_cell(line, column, value);
    m_grid->set_filled_cell({line, column});

    qDebug() << "Filled [" << line << "][" << column << "] with : " << value;
}

bool
Solver::check_lines(const Raw_grid & grid, const size_t & line, const size_t & column) const
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
Solver::check_line_1st_case(const Raw_grid & grid, const size_t & line, const size_t & column, const size_t & row_of_1st_number) const
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
Solver::check_line_2nd_case(const Raw_grid & grid, const size_t & line, const size_t & column, const size_t & row_of_1st_number) const
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
Solver::check_line_3rd_case(const Raw_grid & grid, const size_t & line, const size_t & column, const size_t & row_of_1st_number) const
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
Solver::check_number_in_line(const Raw_grid & grid, const size_t & line, const int number) const
{
    for (size_t column_check = 0; column_check < 9; ++column_check)
    {
        if (grid[line][column_check] == number)
            return (column_check / 3 + 1);
    }
    return 0;
}

int
Solver::check_full_rows_in_line(const Raw_grid & grid, const size_t & line, const int row_of_found_number, const int number_to_check) const
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
                                        const int row_of_2nd_number) const
{
    if (row_of_1st_number == 1)             // The First number is in the 1st rows of 3 cells (|X|X|X|3|4|5|6|7|8|)
    {
        if (row_of_2nd_number == 2)         // The Second number is in the 2nd rows (|0|1|2|X|X|X|6|7|8|)
            return try_to_fill_number_in_3rd_row_of_line(grid, line_to_fill, number_to_fill);
        else if (row_of_2nd_number == 3)    // The Second number is in the 3rd rows (|0|1|2|3|4|5|X|X|X|)
            return try_to_fill_number_in_2nd_row_of_line(grid, line_to_fill, number_to_fill);
        else    // Should never go here
            qDebug() << "/!\\ Same rows ?!" << " 1st_row is " << row_of_1st_number << " & 2nd_row is " << row_of_2nd_number;
    }

    else if (row_of_1st_number == 2)
    {
        if (row_of_2nd_number == 1)
            return try_to_fill_number_in_3rd_row_of_line(grid, line_to_fill, number_to_fill);
        else if (row_of_2nd_number == 3)
            return try_to_fill_number_in_1st_row_of_line(grid, line_to_fill, number_to_fill);
        else    // Should never go here
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
Solver::try_to_fill_number_in_1st_row_of_line(const Raw_grid & grid, const size_t line_to_fill, const int number_to_fill) const
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
Solver::try_to_fill_number_in_2nd_row_of_line(const Raw_grid & grid, const size_t line_to_fill, const int number_to_fill) const
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
        qDebug() << "already there";
    else
        qDebug() << "too many possibilities";*/

    return false;
}

// We are then trying to fill here |0|1|2|3|4|5|X|X|X|
bool
Solver::try_to_fill_number_in_3rd_row_of_line(const Raw_grid & grid, const size_t line_to_fill, const int number_to_fill) const
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
        qDebug() << "already there";
    else
        qDebug() << "too many possibilities";*/


    return false;
}


bool
Solver::check_columns(const Raw_grid & grid, const size_t & line, const size_t & column) const
{
    const size_t COLUMN = (column + 1) % 3;
    int row_of_1st_number = line / 3 + 1;

    // First case
    // COLUMN Number found      COLUMN To check          COLUMN To check
    if (COLUMN == 1)
        return check_column_1st_case(grid, line, column, row_of_1st_number);

    // Second case
    // COLUMN To check          COLUMN Number found     COLUMN To check
    else if (COLUMN == 2)
        return check_column_2nd_case(grid, line, column, row_of_1st_number);

    // Third case
    // COLUMN To check          COLUMN To check         COLUMN Number found
    else if (COLUMN == 0)
        return check_column_3rd_case(grid, line, column, row_of_1st_number);

    else // Should never go here
        qDebug() << "What am I doing here ?!" << " COLUMN is " << COLUMN;

    return false;
}

bool
Solver::check_column_1st_case(const Raw_grid & grid, const size_t & line, const size_t & column, const size_t & row_of_1st_number) const
{
    //qDebug() << "In COLUMN Case 1";

    // Checking for the number in other columns
    if (int row_of_2nd_number = check_number_in_column(grid, column + 1, grid[line][column]))
        return try_to_fill_number_in_row_of_columns(grid, column + 2, grid[line][column], row_of_1st_number, row_of_2nd_number);

    if (int row_of_2nd_number = check_number_in_column(grid, column + 2, grid[line][column]))
        return try_to_fill_number_in_row_of_columns(grid, column + 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    // Checking for full rows in other columns
    if (int row_of_2nd_number = check_full_rows_in_columns(grid, column + 1, row_of_1st_number, grid[line][column]))
        return try_to_fill_number_in_row_of_columns(grid, column + 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    if (int row_of_2nd_number = check_full_rows_in_columns(grid, column + 2, row_of_1st_number, grid[line][column]))
        return try_to_fill_number_in_row_of_columns(grid, column + 2, grid[line][column], row_of_1st_number, row_of_2nd_number);


    //qDebug() << "Number " << grid[line][column] << " not found on other columns";
    return false;
}

bool
Solver::check_column_2nd_case(const Raw_grid & grid, const size_t & line, const size_t & column, const size_t & row_of_1st_number) const
{
    //qDebug() << "In COLUMN Case 2";

    // Checking for the number in other columns
    if (int row_of_2nd_number = check_number_in_column(grid, column - 1, grid[line][column]))
        return try_to_fill_number_in_row_of_columns(grid, column + 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    if (int row_of_2nd_number = check_number_in_column(grid, column + 1, grid[line][column]))
        return try_to_fill_number_in_row_of_columns(grid, column - 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    // Checking for full rows in other columns
    if (int row_of_2nd_number = check_full_rows_in_columns(grid, column - 1, row_of_1st_number, grid[line][column]))
        return try_to_fill_number_in_row_of_columns(grid, column - 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    if (int row_of_2nd_number = check_full_rows_in_columns(grid, column + 1, row_of_1st_number, grid[line][column]))
        return try_to_fill_number_in_row_of_columns(grid, column + 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    //qDebug() << "Number " << grid[line][column] << " not found on other columns";
    return false;
}

bool
Solver::check_column_3rd_case(const Raw_grid & grid, const size_t & line, const size_t & column, const size_t & row_of_1st_number) const
{
    //qDebug() << "In COLUMN Case 3";

    // Checking for the number in other columns
    if (int row_of_2nd_number = check_number_in_column(grid, column - 1, grid[line][column]))
        return try_to_fill_number_in_row_of_columns(grid, column - 2, grid[line][column], row_of_1st_number, row_of_2nd_number);

    if (int row_of_2nd_number = check_number_in_column(grid, column - 2, grid[line][column]))
        return try_to_fill_number_in_row_of_columns(grid, column - 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    // Checking for full rows in other columns
    if (int row_of_2nd_number = check_full_rows_in_columns(grid, column - 1, row_of_1st_number, grid[line][column]))
        return try_to_fill_number_in_row_of_columns(grid, column - 1, grid[line][column], row_of_1st_number, row_of_2nd_number);

    if (int row_of_2nd_number = check_full_rows_in_columns(grid, column - 2, row_of_1st_number, grid[line][column]))
        return try_to_fill_number_in_row_of_columns(grid, column - 2, grid[line][column], row_of_1st_number, row_of_2nd_number);

    //qDebug() << "Number " << grid[line][column] << " not found on other columns";
    return false;
}

int
Solver::check_number_in_column(const Raw_grid & grid, const size_t & column, const int number) const
{
    for (size_t line_check = 0; line_check < 9; ++line_check)
    {
        if (grid[line_check][column] == number)
            return (line_check / 3 + 1);
    }
    return 0;
}

int
Solver::check_full_rows_in_columns(const Raw_grid & grid, const size_t & column, const int row_of_found_number, const int number_to_check) const
{
    int numbers_in_row = 0;

    for (size_t line_check = 0; line_check < 9; ++line_check)
    {
        if (grid[line_check][column] ||
            m_grid->is_number_in_line(line_check, number_to_check))
            numbers_in_row++;

        if ((line_check + 1) % 3 == 0)
        {
            if (numbers_in_row == 3 &&
                row_of_found_number != line_check / 3 + 1)
                return (line_check / 3 + 1);  // Number not found but the row is already full or can not be filled with it
            else
                numbers_in_row = 0;
        }
    }
    return 0;
}

bool
Solver::try_to_fill_number_in_row_of_columns(const Raw_grid & grid, const size_t column_to_fill, const int number_to_fill, const int row_of_1st_number, const int row_of_2nd_number) const
{
    if (row_of_1st_number == 1)
    {
        if (row_of_2nd_number == 2)
            return try_to_fill_number_in_3rd_row_of_column(grid, column_to_fill, number_to_fill);
        else if (row_of_2nd_number == 3)
            return try_to_fill_number_in_2nd_row_of_column(grid, column_to_fill, number_to_fill);
        else // Should never go here
            qDebug() << "/!\\ Same rows ?!" << " 1st_row is " << row_of_1st_number << " & 2nd_row is " << row_of_2nd_number;
    }

    else if (row_of_1st_number == 2)
    {
        if (row_of_2nd_number == 1)
            return try_to_fill_number_in_3rd_row_of_column(grid, column_to_fill, number_to_fill);
        else if (row_of_2nd_number == 3)
            return try_to_fill_number_in_1st_row_of_column(grid, column_to_fill, number_to_fill);
        else // Should never go here
            qDebug() << "/!\\ Same rows ?!" << " 1st_row is " << row_of_1st_number << " & 2nd_row is " << row_of_2nd_number;
    }

    else if (row_of_1st_number == 3)   // Third rows of 3 cells
    {
        if (row_of_2nd_number == 1)
            return try_to_fill_number_in_2nd_row_of_column(grid, column_to_fill, number_to_fill);
        else if (row_of_2nd_number == 2)
            return try_to_fill_number_in_1st_row_of_column(grid, column_to_fill, number_to_fill);
        else // Should never go here
            qDebug() << "/!\\ Same rows ?!" << " 1st_row is " << row_of_1st_number << " & 2nd_row is " << row_of_2nd_number;
    }

    else    // Should never go here
        qDebug() << "What am I doing here ?!" << " 1st_row is " << row_of_1st_number;

    return false;
}

// We are trying to fill here |X|
//                            |X|
//                            |X|
//                            |3|
//                            |4|
//                            |5|
//                            |6|
//                            |7|
//                            |8|
bool
Solver::try_to_fill_number_in_1st_row_of_column(const Raw_grid & grid, const size_t column_to_fill, const int number_to_fill) const
{
    bool has_number = false;
    int number_of_blank = 0;
    size_t cell_to_fill = 0;

    for (size_t cell = 0; cell < 3; cell++)
    {
        if (grid[cell][column_to_fill] == 0)
        {
            // Checking the line to see if it has number_to_fill
            if (!m_grid->is_number_in_line(cell, number_to_fill))
            {
                number_of_blank++;
                cell_to_fill = cell;
            }
        }
        else if (grid[cell][column_to_fill] == number_to_fill)
            has_number = true;
    }

    if (!has_number && number_of_blank == 1)
    {
        // Finally filling the grid
        fill_grid(cell_to_fill, column_to_fill, number_to_fill);

        return true;
    }

    /*qDebug() << "Could not fill 1st row of column with " << number_to_fill << " -> ";
    if (has_number)
        qDebug() << "already there";
    else
        qDebug() << "too many possibilities";*/

    return false;
}

// We are trying to fill here |0|
//                            |1|
//                            |2|
//                            |X|
//                            |X|
//                            |X|
//                            |6|
//                            |7|
//                            |8|
bool
Solver::try_to_fill_number_in_2nd_row_of_column(const Raw_grid & grid, const size_t column_to_fill, const int number_to_fill) const
{
    bool has_number = false;
    int number_of_blank = 0;
    size_t cell_to_fill = 0;

    for (size_t cell = 3; cell < 6; cell++)
    {
        if (grid[cell][column_to_fill] == 0)
        {
            // Checking the line to see if it has number_to_fill
            if (!m_grid->is_number_in_line(cell, number_to_fill))
            {
                number_of_blank++;
                cell_to_fill = cell;
            }
        }
        else if (grid[cell][column_to_fill] == number_to_fill)
            has_number = true;
    }

    if (!has_number && number_of_blank == 1)
    {
        // Finally filling the grid
        fill_grid(cell_to_fill, column_to_fill, number_to_fill);

        return true;
    }

    /*qDebug() << "Could not fill 1st row of column with " << number_to_fill << " -> ";
    if (has_number)
        qDebug() << "already there";
    else
        qDebug() << "too many possibilities";*/

    return false;
}

// We are trying to fill here |0|
//                            |1|
//                            |2|
//                            |3|
//                            |4|
//                            |5|
//                            |X|
//                            |X|
//                            |X|
bool
Solver::try_to_fill_number_in_3rd_row_of_column(const Raw_grid & grid, const size_t column_to_fill, const int number_to_fill) const
{
    bool has_number = false;
    int number_of_blank = 0;
    size_t cell_to_fill = 0;

    for (size_t cell = 6; cell < 9; cell++)
    {
        if (grid[cell][column_to_fill] == 0)
        {
            // Checking the line to see if it has number_to_fill
            if (!m_grid->is_number_in_line(cell, number_to_fill))
            {
                number_of_blank++;
                cell_to_fill = cell;
            }
        }
        else if (grid[cell][column_to_fill] == number_to_fill)
            has_number = true;
    }

    if (!has_number && number_of_blank == 1)
    {
        // Finally filling the grid
        fill_grid(cell_to_fill, column_to_fill, number_to_fill);
        return true;
    }

    /*qDebug() << "Could not fill 1st row of column with " << number_to_fill << " -> ";
    if (has_number)
        qDebug() << "already there";
    else
        qDebug() << "too many possibilities";*/

    return false;
}


// We might have a chance to fill the line with a missing number on that line
bool
Solver::try_to_fill_line(const size_t line) const
{
    std::vector<int>    numbers{ 1,2,3,4,5,6,7,8,9 };
    std::vector<int>    numbers_in_line;
    std::vector<int>    missing_numbers;
    std::vector<size_t> blank_columns;


    for (size_t column_check = 0; column_check < 9; ++column_check)
    {
        if ((*m_grid)[line][column_check])
            numbers_in_line.push_back((*m_grid)[line][column_check]);
        else
            blank_columns.push_back(column_check);
    }

    std::sort(numbers_in_line.begin(), numbers_in_line.end());
    std::set_difference(numbers.begin(), numbers.end(),
                        numbers_in_line.begin(), numbers_in_line.end(),
                        std::back_inserter(missing_numbers));

    /*qDebug() << "Missing numbers in line " << line << " : ";
        for (auto & number : missing_numbers)
            qDebug() << number << " ";

        qDebug() << "In maybe column : ";
        for (auto & blank_column : blank_columns)
            qDebug() << blank_column << " ";
    */


    // Hurray, only one possibility !
    if (missing_numbers.size() == 1) {
        fill_grid(line, blank_columns.front(), missing_numbers.front());
        return true;
    }
    else if (missing_numbers.size() == 2)
        return try_to_fill_line_with_2_blank_space(line, missing_numbers, blank_columns);

    else if (missing_numbers.size() == 3)
        return try_to_fill_line_with_more_blank_space(line, missing_numbers, blank_columns);

    return false;
}

bool
Solver::try_to_fill_line_with_2_blank_space(const size_t line,
                                           const std::vector<int> & missing_numbers,
                                           const std::vector<size_t> & blank_columns) const
{
    auto & blank_column_one = blank_columns.front();
    auto & blank_column_two = blank_columns.back();

    for (auto & missing_number : missing_numbers)
    {
        if (m_grid->is_number_in_column(blank_column_one, missing_number))
        {
            fill_grid(line, blank_column_two, missing_number);
            return true;
        }
        if (m_grid->is_number_in_column(blank_column_two, missing_number))
        {
            fill_grid(line, blank_column_one, missing_number);
            return true;
        }
    }

    return false;
}

bool
Solver::try_to_fill_line_with_more_blank_space(const size_t line,
                                            const std::vector<int> & missing_numbers,
                                            const std::vector<size_t> & blank_columns) const
{
    for (auto it = blank_columns.begin() ;
         it != blank_columns.end();
         ++it)
    {
        // We will emplace the times a missing number is found at this number (-1) location
        std::vector<size_t>     found_numbers = { 0,0,0,0,0,0,0,0,0 };

        // We are checking every blank column
        for (auto blank_column = blank_columns.begin();
             blank_column != blank_columns.end();
             ++blank_column)
        {
            if (blank_column != it)
            {
                // For every missing number
                for (auto & missing_number : missing_numbers)
                {
                    if (m_grid->is_number_in_column(*blank_column, missing_number))
                        found_numbers[missing_number - 1]++;
                }
            }
        }

        // Did we find a missing number enough times
        for (auto found_number = found_numbers.begin();
             found_number != found_numbers.end();
             ++found_number)
        {
            // We need to have found it as much as there are missing numbers
            if (*found_number == missing_numbers.size() - 1)
            {
                size_t number_to_fill = std::distance(found_numbers.begin(), found_number) + 1;

                fill_grid(line, *it, number_to_fill);
                return true;
            }
        }

        // Reseting
        for (auto & found_number : found_numbers)
            found_number = 0;
    }

    return false;
}


// We might have a chance to fill the column with a missing number on that column
bool
Solver::try_to_fill_column(const size_t column) const
{
    std::vector<int>    numbers{ 1,2,3,4,5,6,7,8,9 };
    std::vector<int>    numbers_in_column;
    std::vector<int>    missing_numbers;
    std::vector<size_t> blank_lines;


    for (size_t line_check = 0; line_check < 9; ++line_check)
    {
        if ((*m_grid)[line_check][column])
            numbers_in_column.push_back((*m_grid)[line_check][column]);
        else
            blank_lines.push_back(line_check);
    }

    std::sort(numbers_in_column.begin(), numbers_in_column.end());
    std::set_difference(numbers.begin(), numbers.end(),
                        numbers_in_column.begin(), numbers_in_column.end(),
                        std::back_inserter(missing_numbers));

    if (missing_numbers.size() == 1) {

        fill_grid(blank_lines.front(), column, missing_numbers.front());
        return true;
    }
    else if (missing_numbers.size() == 2)
        return try_to_fill_column_with_2_blank_space(column, missing_numbers, blank_lines);

    else if (missing_numbers.size() == 3)
        // Could work with more than 3 blank space but would be costly
        return try_to_fill_column_with_more_blank_space(column, missing_numbers, blank_lines);

    return false;
}

bool
Solver::try_to_fill_column_with_2_blank_space(const size_t column,
                                            const std::vector<int> & missing_numbers,
                                            const std::vector<size_t> & blank_lines) const
{
    auto & blank_line_one = blank_lines.front();
    auto & blank_line_two = blank_lines.back();

    for (auto & missing_number : missing_numbers)
    {
        if (m_grid->is_number_in_line(blank_line_one, missing_number))
        {
            fill_grid(blank_line_two, column, missing_number);
            return true;
        }
        if (m_grid->is_number_in_line(blank_line_two, missing_number))
        {
            fill_grid(blank_line_one, column, missing_number);
            return true;
        }
    }

    return false;
}

bool
Solver::try_to_fill_column_with_more_blank_space(const size_t column,
                                             const std::vector<int> & missing_numbers,
                                             const std::vector<size_t> & blank_lines) const
{
    for (auto it = blank_lines.begin();
         it != blank_lines.end();
         ++it)
    {
        // We will emplace the times a missing number is found at this number (-1) location
        std::vector<size_t>     found_numbers = { 0,0,0,0,0,0,0,0,0 };

        // We are checking every blank line
        for (auto blank_line = blank_lines.begin();
             blank_line != blank_lines.end();
             ++blank_line)
        {
            if (blank_line != it)
            {
                // For every missing number
                for (auto & missing_number : missing_numbers)
                {
                    if (m_grid->is_number_in_line(*blank_line, missing_number))
                        found_numbers[missing_number - 1]++;
                }
            }
        }

        // Did we find a missing number enough times
        for (auto found_number = found_numbers.begin();
             found_number != found_numbers.end();
             ++found_number)
        {
            // We need to have found it as much as there are missing numbers
            if (*found_number == missing_numbers.size() - 1)
            {
                size_t number_to_fill = std::distance(found_numbers.begin(), found_number) + 1;

                fill_grid(*it, column, number_to_fill);
                return true;
            }
        }

        // Reseting
        for (auto & found_number : found_numbers)
            found_number = 0;
    }

    return false;
}
