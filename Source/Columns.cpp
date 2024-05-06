#include "Grid.h"
#include <iostream>
#include <algorithm>

bool check_line_for_number(Grid & grid, const size_t line, const int number_to_check)
{
    for (size_t column_check = 0; column_check < 9; ++column_check)
    {
        if (grid[line][column_check] == number_to_check)
            return true;
    }
    return false;
}

// We are trying to fill here |0|X
//                            |1|X
//                            |2|X
//                            |3|
//                            |4|
//                            |5|
//                            |6|
//                            |7|
//                            |8|
bool try_to_fill_number_in_1st_row_of_column(Grid & grid, const size_t column_to_fill, const int number_to_fill)
{
    bool has_number = false;
    int number_of_blank = 0;
    size_t cell_to_fill = 0;

    for (size_t cell = 0; cell < 3; cell++)
    {
        if (grid[cell][column_to_fill] == 0)
        {
            // Checking the line to see if it has number_to_fill 
            if (!check_line_for_number(grid, cell, number_to_fill))
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
        grid[cell_to_fill][column_to_fill] = number_to_fill;
        std::cout << "//!// Filled 1st row of column [" << column_to_fill << "] in line [" << cell_to_fill << "] with " << number_to_fill << std::endl << std::endl;

        return true;
    }

    /*std::cout << "Could not fill 1st row of column with " << number_to_fill << " -> ";
    if (has_number)
        std::cout << "already there" << std::endl;
    else
        std::cout << "too many possibilities" << std::endl;*/

    return false;
}

// We are trying to fill here |0|
//                            |1|
//                            |2|
//                            |3|X
//                            |4|X
//                            |5|X
//                            |6|
//                            |7|
//                            |8|
bool try_to_fill_number_in_2nd_row_of_column(Grid & grid, const size_t column_to_fill, const int number_to_fill)
{
    bool has_number = false;
    int number_of_blank = 0;
    size_t cell_to_fill = 0;

    for (size_t cell = 3; cell < 6; cell++)
    {
        if (grid[cell][column_to_fill] == 0)
        {
            // Checking the line to see if it has number_to_fill 
            if (!check_line_for_number(grid, cell, number_to_fill))
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
        grid[cell_to_fill][column_to_fill] = number_to_fill;
        std::cout << "//!// Filled 2nd row of column [" << column_to_fill << "] in line [" << cell_to_fill << "] with " << number_to_fill << std::endl << std::endl;

        return true;
    }

    /*std::cout << "Could not fill 2nd row of column with " << number_to_fill << " -> ";
    if (has_number)
        std::cout << "already there" << std::endl;
    else
        std::cout << "too many possibilities" << std::endl;*/

    return false;
}

// We are trying to fill here |0|
//                            |1|
//                            |2|
//                            |3|
//                            |4|
//                            |5|
//                            |6|X
//                            |7|X
//                            |8|X
bool    try_to_fill_number_in_3rd_row_of_column(Grid & grid, const size_t column_to_fill, const int number_to_fill)
{
    bool has_number = false;
    int number_of_blank = 0;
    size_t cell_to_fill = 0;

    for (size_t cell = 6; cell < 9; cell++)
    {
        if (grid[cell][column_to_fill] == 0)
        {
            // Checking the line to see if it has number_to_fill
            if (!check_line_for_number(grid, cell, number_to_fill))
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
        grid[cell_to_fill][column_to_fill] = number_to_fill;
        std::cout << "//!// Filled 3rd row of column [" << column_to_fill << "] in line [" << cell_to_fill << "] with " << number_to_fill << std::endl << std::endl;

        return true;
    }

    /*std::cout << "Could not fill 3rd row of column with " << number_to_fill << " -> ";
    if (has_number)
        std::cout << "already there" << std::endl;
    else
        std::cout << "too many possibilities" << std::endl;*/

    return false;
}

bool    try_to_fill_number_in_row_of_columns(Grid & grid, const size_t column_to_fill, const int number_to_fill, const int row_of_cells, const int row)
{
    if (row_of_cells == 1)        // First rows of 3 cells
    {
        if (row == 2)
        {
           // std::cout << "Trying to fill " << number_to_fill << " in last third of column" << std::endl;
            return try_to_fill_number_in_3rd_row_of_column(grid, column_to_fill, number_to_fill);
        }
        else if (row == 3)
        {
            //std::cout << "Trying to fill " << number_to_fill << " in middle of column" << std::endl;
            return try_to_fill_number_in_2nd_row_of_column(grid, column_to_fill, number_to_fill);
        }
        else // Should never go here
            std::cerr << "What am I doing here ?!" << " row is " << row << std::endl << std::endl;
    }

    else if (row_of_cells == 2)   // Second rows of 3 cells
    {
        if (row == 1)
        {
            //std::cout << "Trying to fill " << number_to_fill << " in last third of column" << std::endl;
            return try_to_fill_number_in_3rd_row_of_column(grid, column_to_fill, number_to_fill);
        }
        else if (row == 3)
        {
            //std::cout << "Trying to fill " << number_to_fill << " in first third of column" << std::endl;
            return try_to_fill_number_in_1st_row_of_column(grid, column_to_fill, number_to_fill);
        }
        else // Should never go here
            std::cerr << "What am I doing here ?!" << " row is " << row << std::endl << std::endl;
    }

    else if (row_of_cells == 3)   // Third rows of 3 cells
    {
        if (row == 1)
        {
            //std::cout << "Trying to fill " << number_to_fill << " in middle of column" << std::endl;
            return try_to_fill_number_in_2nd_row_of_column(grid, column_to_fill, number_to_fill);
        }
        else if (row == 2)
        {
            //std::cout << "Trying to fill " << number_to_fill << " in first third of column" << std::endl;
           return try_to_fill_number_in_1st_row_of_column(grid, column_to_fill, number_to_fill);
        }
        else // Should never go here
            std::cerr << "What am I doing here ?!" << " row is " << row << std::endl << std::endl;
    }

    else    // Should never go here
        std::cerr << "What am I doing here ?!" << " number_row is " << row_of_cells << std::endl << std::endl;

    return false;
}


int     check_full_rows_in_columns(Grid & grid, const size_t & column, const int row_of_found_number, const int number_to_check)
{
    int numbers_in_row = 0;

    for (size_t line_check = 0; line_check < 9; ++line_check)
    {
        if (grid[line_check][column] ||
            check_line_for_number(grid, line_check, number_to_check))
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

int     check_number_in_column(Grid & grid, const size_t & column, const int number)
{
    for (size_t line_check = 0; line_check < 9; ++line_check)
    {
        if (grid[line_check][column] == number)
        {
            //std::cout << "|" << line_check << "| / 3 + 1 = " << line_check / 3 + 1 << std::endl;
            return (line_check / 3 + 1);
        }
    }
    return 0;
}

bool    check_columns(Grid & grid, const size_t & line, const size_t & column)
{
    const size_t COLUMN = (column + 1) % 3;
    int row_of_cells = line / 3 + 1;

    // First case 
    // COLUMN Number found      COLUMN To check     COLUMN To check
    if (COLUMN == 1)
    {
        std::cout << "In COLUMN Case 1" << std::endl;

        // Checking for the number in other columns
        if (int row = check_number_in_column(grid, column + 1, grid[line][column])) {
            //std::cout << "Found number " << grid[line][column] << " in 2nd column & row are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_columns(grid, column + 2, grid[line][column], row_of_cells, row);
        }
        if (int row = check_number_in_column(grid, column + 2, grid[line][column])) {
            //std::cout << "Found number " << grid[line][column] << " in 3rd column & row are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_columns(grid, column + 1, grid[line][column], row_of_cells, row);
        }

        // Checking for full rows in other columns
        if (int row = check_full_rows_in_columns(grid, column + 1, row_of_cells, grid[line][column])) {
            //std::cout << "Found full row in 2nd column & rows are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_columns(grid, column + 1, grid[line][column], row_of_cells, row);
        }
        if (int row = check_full_rows_in_columns(grid, column + 2, row_of_cells, grid[line][column])) {
            //std::cout << "Found full row in 3rd column & rows are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_columns(grid, column + 2, grid[line][column], row_of_cells, row);
        }

        //std::cout << "Number " << grid[line][column] << " not found on other columns" << std::endl;
        return false;
    }

    // Second case 
    // COLUMN To check      COLUMN Number found     COLUMN To check
    else if (COLUMN == 2)
    {
       std::cout << "In COLUMN Case 2" << std::endl;

       // Checking for the number in other columns
        if (int row = check_number_in_column(grid, column - 1, grid[line][column])) {
            //std::cout << "Found number " << grid[line][column] << " in 2nd column & row are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_columns(grid, column + 1, grid[line][column], row_of_cells, row);
        }
        if (int row = check_number_in_column(grid, column + 1, grid[line][column])) {
            //std::cout << "Found number " << grid[line][column] << " in 3rd column & row are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_columns(grid, column - 1, grid[line][column], row_of_cells, row);
        }

        // Checking for full rows in other columns
        if (int row = check_full_rows_in_columns(grid, column - 1, row_of_cells, grid[line][column])) {
            //std::cout << "Found full row in 1st column & rows are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_columns(grid, column - 1, grid[line][column], row_of_cells, row);
        }
        if (int row = check_full_rows_in_columns(grid, column + 1, row_of_cells, grid[line][column])) {
            //std::cout << "Found full row in 3rd column & rows are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_columns(grid, column + 1, grid[line][column], row_of_cells, row);
        }

        //std::cout << "Number " << grid[line][column] << " not found on other columns" << std::endl;
        return false;
    }

    // Third case 
    // COLUMN To check      COLUMN To check     COLUMN Number found
    else if (COLUMN == 0)
    {
        std::cout << "In COLUMN Case 3 : " << line << ";" << column << std::endl;

        // Checking for the number in other columns
        if (int row = check_number_in_column(grid, column - 1, grid[line][column])) {
            //std::cout << "Found number " << grid[line][column] << " in 2nd column & row are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_columns(grid, column - 2, grid[line][column], row_of_cells, row);
        }
        if (int row = check_number_in_column(grid, column - 2, grid[line][column])) {
            //std::cout << "Found number " << grid[line][column] << " in 3rd column & row are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_columns(grid, column - 1, grid[line][column], row_of_cells, row);
        }

        // Checking for full rows in other columns
        if (int row = check_full_rows_in_columns(grid, column - 1, row_of_cells, grid[line][column])) {
            //std::cout << "Found full row in 1st column & rows are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_columns(grid, column - 1, grid[line][column], row_of_cells, row);
        }
        if (int row = check_full_rows_in_columns(grid, column - 2, row_of_cells, grid[line][column])) {
            //std::cout << "Found full row in 2nd column & rows are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_columns(grid, column - 2, grid[line][column], row_of_cells, row);
        }

        //std::cout << "Number " << grid[line][column] << " not found on other columns" << std::endl;
        return false;
    }

    else // Should never go here
        std::cerr << "What am I doing here ?!" << " COLUMN is " << COLUMN << std::endl << std::endl;

    return false;

}

bool try_to_fill_column(Grid & grid, const size_t column,
    const std::vector<int> & missing_numbers,
    const std::vector<size_t> & blank_lines)
{
    auto & blank_line_one = blank_lines.front();
    auto & blank_line_two = blank_lines.back();

    for (auto & missing_number : missing_numbers)
    {
        if (check_line_for_number(grid, blank_line_one, missing_number))
        {
            std::cout << "||!|| Filled line " << blank_line_two << " column " << column << " with : " << missing_number << std::endl << std::endl;
            grid[blank_line_two][column] = missing_number;
            return true;
        }
        if (check_line_for_number(grid, blank_line_two, missing_number))
        {
            std::cout << "||!|| Filled line " << blank_line_one << " column " << column << " with : " << missing_number << std::endl << std::endl;
            grid[blank_line_one][column] = missing_number;
            return true;
        }
    }

    return false;
}

// Can we fill the column with a missing number
bool can_fill_column(Grid & grid, const size_t column)
{
    std::vector<int>    numbers{ 1,2,3,4,5,6,7,8,9 };
    std::vector<int>    numbers_in_column;
    std::vector<int>    missing_numbers;
    std::vector<size_t> blank_lines;


    for (size_t line_check = 0; line_check < 9; ++line_check)
    {
        if (grid[line_check][column])
            numbers_in_column.push_back(grid[line_check][column]);
        else
            blank_lines.push_back(line_check);
    }

    std::sort(numbers_in_column.begin(), numbers_in_column.end());
    std::set_difference(numbers.begin(), numbers.end(),
        numbers_in_column.begin(), numbers_in_column.end(),
        std::back_inserter(missing_numbers));

    // We might have a chance to fill the column with a missing number on that column
    if (missing_numbers.size() == 1)
    {
        std::cout << "|!| Filled line " << blank_lines.front() << " column " << column << " with : " << missing_numbers.front() << std::endl << std::endl;
        grid[blank_lines.front()][column] = missing_numbers.front();
        return true;
    }
    else if (missing_numbers.size() == 2)
        return try_to_fill_column(grid, column, missing_numbers, blank_lines);

    return false;
}