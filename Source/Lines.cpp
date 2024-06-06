#pragma once

#include "Grid.h"
#include <iostream>
#include <algorithm>

bool check_column_for_number(Grid & grid, const size_t column, const int number_to_check)
{
    for (size_t line_check = 0; line_check < 9; ++line_check)
    {
        if (grid[line_check][column] == number_to_check)
            return true;
    }
    return false;
}

// We are trying to fill here |0|1|2|3|4|5|6|7|8|
//                             X|X|X
bool try_to_fill_number_in_1st_row_of_line(Grid & grid, const size_t line_to_fill, const int number_to_fill)
{
    bool has_number = false;
    int number_of_blank = 0;
    size_t cell_to_fill = 0;

    for (size_t cell = 0; cell < 3; cell++)
    {
        if (grid[line_to_fill][cell] == 0)
        {
            // Checking the column to see if it has number_to_fill 
            if (!check_column_for_number(grid, cell, number_to_fill))
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
        grid[line_to_fill][cell_to_fill] = number_to_fill;
        std::cout << "//!// Filled 1st row of line " << line_to_fill << " in column [" << cell_to_fill << "] with " << number_to_fill << std::endl << std::endl;

        return true;
    }

    /*std::cout << "Could not fill 1st row of line with " << number_to_fill << " -> ";
    if (has_number)
        std::cout << "already there" << std::endl;
    else
        std::cout << "too many possibilities" << std::endl;*/

    return false;
}

// We are trying to fill here |0|1|2|3|4|5|6|7|8|
//                                   X|X|X
bool try_to_fill_number_in_2nd_row_of_line(Grid & grid, const size_t line_to_fill, const int number_to_fill)
{
    bool has_number = false;
    int number_of_blank = 0;
    size_t cell_to_fill = 0;

    for (size_t cell = 3; cell < 6; cell++)
    {
        if (grid[line_to_fill][cell] == 0)
        {
            // Checking the column to see if it has number_to_fill 
            if (!check_column_for_number(grid, cell, number_to_fill))  
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
        grid[line_to_fill][cell_to_fill] = number_to_fill;
        std::cout << "//!// Filled 2nd row of line " << line_to_fill << " in column [" << cell_to_fill << "] with " << number_to_fill << std::endl << std::endl;

        return true;
    }

    /*std::cout << "Could not fill 2nd row of line with " << number_to_fill << " -> ";
    if (has_number)
        std::cout << "already there" << std::endl;
    else
        std::cout << "too many possibilities" << std::endl;*/

    return false;
}

// We are trying to fill here |0|1|2|3|4|5|6|7|8|
//                                         X|X|X
bool try_to_fill_number_in_3rd_row_of_line(Grid & grid, const size_t line_to_fill, const int number_to_fill)
{
    bool has_number = false;
    int number_of_blank = 0;
    size_t cell_to_fill = 0;

    for (size_t cell = 6; cell < 9; cell++)
    {
        if (grid[line_to_fill][cell] == 0)
        {
            // Checking the column to see if it has number_to_fill 
            if (!check_column_for_number(grid, cell, number_to_fill))
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
        grid[line_to_fill][cell_to_fill] = number_to_fill;
        std::cout << "//!// Filled 3rd row of line " << line_to_fill << " in column [" << cell_to_fill << "] with " << number_to_fill << std::endl << std::endl;

        return true;
    }

    /*std::cout << "Could not fill 3rd row of line with " << number_to_fill << " -> ";
    if (has_number)
        std::cout << "already there" << std::endl;
    else
        std::cout << "too many possibilities" << std::endl;*/

    return false;
}


bool try_to_fill_number_in_row_of_line(Grid & grid, const size_t line_to_fill, const int number_to_fill, const int row_of_cells, const int row)
{
    if (row_of_cells == 1)        // First rows of 3 cells
    {
        if (row == 2)
        {
            //std::cout << "Trying to fill " << number_to_fill << " in here |0|1|2|3|4|5|X|X|X|" << std::endl;
            return try_to_fill_number_in_3rd_row_of_line(grid, line_to_fill, number_to_fill);
        }
        else if (row == 3)
        {
            //std::cout << "Trying to fill " << number_to_fill << " in here |0|1|2|X|X|X|6|7|8|" << std::endl;
            return try_to_fill_number_in_2nd_row_of_line(grid, line_to_fill, number_to_fill);
        }
        else // Should never go here
            std::cerr << "/!\\ Same rows ?!" << " row_of_cells is " << row_of_cells << " & row is " << row << std::endl << std::endl;
    }

    else if (row_of_cells == 2)   // Second rows of 3 cells
    {
        if (row == 1)
        {
            //std::cout << "Trying to fill " << number_to_fill << " in here |0|1|2|3|4|5|X|X|X|" << std::endl;
            return try_to_fill_number_in_3rd_row_of_line(grid, line_to_fill, number_to_fill);
        }
        else if (row == 3)
        {
            //std::cout << "Trying to fill " << number_to_fill << " in here |X|X|X|3|4|5|6|7|8|" << std::endl;
            return try_to_fill_number_in_1st_row_of_line(grid, line_to_fill, number_to_fill);
        }
        else // Should never go here
            std::cerr << "/!\\ Same rows ?!" << " row_of_cells is " << row_of_cells << " & row is " << row << std::endl << std::endl;
    }

    else if (row_of_cells == 3)   // Third rows of 3 cells
    {
        if (row == 1)
        {
            //std::cout << "Trying to fill " << number_to_fill << " in here |0|1|2|X|X|X|6|7|8|" << std::endl;
            return try_to_fill_number_in_2nd_row_of_line(grid, line_to_fill, number_to_fill);
        }
        else if (row == 2)
        {
            //std::cout << "Trying to fill " << number_to_fill << " in here |X|X|X|3|4|5|6|7|8|" << std::endl;
            return try_to_fill_number_in_1st_row_of_line(grid, line_to_fill, number_to_fill);
        }
        else // Should never go here
            std::cerr << "/!\\ Same rows ?!" << " row_of_cells is " << row_of_cells << " & row is " << row << std::endl << std::endl;
    }

    else    // Should never go here
        std::cerr << "What am I doing here ?!" << " number_row is " << row_of_cells << std::endl << std::endl;

    return false;
}


int check_full_rows_in_line(Grid & grid, const size_t & line, const int row_of_found_number, const int number_to_check)
{
    int numbers_in_row = 0;

    for (size_t column_check = 0; column_check < 9; ++column_check)
    {
        if (grid[line][column_check] ||
            check_column_for_number(grid, column_check, number_to_check))
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

int check_number_in_line(Grid & grid, const size_t & line, const int number)
{
    for (size_t column_check = 0; column_check < 9; ++column_check)
    {
        if (grid[line][column_check] == number)
            return (column_check / 3 + 1);
    }
    return 0;
}

bool check_lines(Grid & grid, const size_t & line, const size_t & column)
{
    const size_t LINE = (line + 1) % 3;
    int row_of_cells = column / 3 + 1;

    // First case 
    // LINE Number found
    // LINE To check
    // LINE To check
    if (LINE == 1)
    {
        //std::cout << "In LINE Case 1" << std::endl;

        // Checking for the number in other lines
        if (int row = check_number_in_line(grid, line + 1, grid[line][column])) {
            //std::cout << "Found number " << grid[line][column] << " in 2nd line & row are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_line(grid, line + 2, grid[line][column], row_of_cells, row);
        }
        if (int row = check_number_in_line(grid, line + 2, grid[line][column])) {
            //std::cout << "Found number " << grid[line][column] << " in 3rd line & row are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_line(grid, line + 1, grid[line][column], row_of_cells, row);
        }

        // Checking for full rows in other lines
        if (int row = check_full_rows_in_line(grid, line + 1, row_of_cells, grid[line][column])) {
            //std::cout << "Found full row in 2nd line & rows are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_line(grid, line + 1, grid[line][column], row_of_cells, row);
        }
        if (int row = check_full_rows_in_line(grid, line + 2, row_of_cells, grid[line][column])) {
            //std::cout << "Found full row in 3rd line & rows are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_line(grid, line + 2, grid[line][column], row_of_cells, row);
        }


        //std::cout << "Number " << grid[line][column] << " not found on other lines" << std::endl;
        return false;
    }

    // Second case 
    // LINE To check
    // LINE Number found
    // LINE To check
    else if (LINE == 2)
    {
        //std::cout << "In LINE Case 2" << std::endl;

        // Checking for the number in other lines
        if (int row = check_number_in_line(grid, line - 1, grid[line][column])) {
            //std::cout << "Found number " << grid[line][column] << " in 1st line & row are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_line(grid, line + 1, grid[line][column], row_of_cells, row);
        }
        if (int row = check_number_in_line(grid, line + 1, grid[line][column])) {
            //std::cout << "Found number " << grid[line][column] << " in 3rd line & row are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_line(grid, line - 1, grid[line][column], row_of_cells, row);
        }

        // Checking for full rows in other lines
        if (int row = check_full_rows_in_line(grid, line - 1, row_of_cells, grid[line][column])) {
            //std::cout << "Found full row in 1st line & rows are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_line(grid, line - 1, grid[line][column], row_of_cells, row);
        }
        if (int row = check_full_rows_in_line(grid, line + 1, row_of_cells, grid[line][column])) {
            //std::cout << "Found full row in 3rd line & rows are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_line(grid, line + 1, grid[line][column], row_of_cells, row);
        }

        //std::cout << "Number " << grid[line][column] << " not found on other lines" << std::endl;
        return false;
    }

    // Third case
    // LINE To check
    // LINE To check
    // LINE Number found
    else if (LINE == 0)
    {
        //std::cout << "In LINE Case 3" << std::endl;

        // Checking for the number in other lines
        if (int row = check_number_in_line(grid, line - 1, grid[line][column])) {
            //std::cout << "Found number " << grid[line][column] << " in 2nd line & row are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_line(grid, line - 2, grid[line][column], row_of_cells, row);
        }
        if (int row = check_number_in_line(grid, line - 2, grid[line][column])) {
            //std::cout << "Found number " << grid[line][column] << " in 1st line & row are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_line(grid, line - 1, grid[line][column], row_of_cells, row);
        }

        // Checking for full rows in other lines
        if (int row = check_full_rows_in_line(grid, line - 1, row_of_cells, grid[line][column])) {
            //std::cout << "Found full row in 2nd line & rows are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_line(grid, line - 1, grid[line][column], row_of_cells, row);
        }
        if (int row = check_full_rows_in_line(grid, line - 2, row_of_cells, grid[line][column])) {
            //std::cout << "Found full row in 1st line & rows are : " << row_of_cells << "/" << row << std::endl;
            return try_to_fill_number_in_row_of_line(grid, line - 2, grid[line][column], row_of_cells, row);
        }

        //std::cout << "Number " << grid[line][column] << " not found on other lines" << std::endl;
        return false;
    }
    
    else // Should never go here
        std::cerr << "What am I doing here ?!" << " LINE is " << LINE << std::endl << std::endl;

    return false;
}


bool try_to_fill_2blank_line(Grid & grid, const size_t line,
    const std::vector<int> & missing_numbers,
    const std::vector<size_t> & blank_columns)
{
    auto & blank_column_one = blank_columns.front();
    auto & blank_column_two = blank_columns.back();
    
    for (auto & missing_number : missing_numbers)
    {
        if (check_column_for_number(grid, blank_column_one, missing_number))
        {
            std::cout << "--!-- Filled line " << line << " column " << blank_column_two << " with : " << missing_number << std::endl << std::endl;
            grid[line][blank_column_two] = missing_number;
            return true;
        }
        if (check_column_for_number(grid, blank_column_two, missing_number))
        {
            std::cout << "--!-- Filled line " << line << " column " << blank_column_one << " with : " << missing_number << std::endl << std::endl;
            grid[line][blank_column_one] = missing_number;
            return true;
        }
    }
            
    return false;
}

bool try_to_fill_3blank_line(Grid & grid, const size_t line,
    const std::vector<int> & missing_numbers,
    const std::vector<size_t> & blank_columns)
{
    for (auto & it = blank_columns.begin() ;
        it != blank_columns.end();
        ++it)
    {
        // We will emplace the times a missing number is found at this number (-1) location
        std::vector<size_t>     found_numbers = { 0,0,0,0,0,0,0,0,0 };

        // We are checking every blank column 
        for (auto & blank_column = blank_columns.begin();
            blank_column != blank_columns.end();
            ++blank_column)
        {
            if (blank_column != it)
            {
                // For every missing number
                for (auto & missing_number : missing_numbers)
                {
                    if (check_column_for_number(grid, *blank_column, missing_number))
                        found_numbers[missing_number - 1]++;
                }
            }

            
        }

        // Did we find a missing number enough times
        for (auto & found_number = found_numbers.begin();
            found_number != found_numbers.end();
            ++found_number)
        {
            if (*found_number == missing_numbers.size() - 1)
            {
                size_t number_to_fill = std::distance(found_numbers.begin(), found_number);

                std::cout << "---!--- Filled line " << line << " column " << *it << " with : " << number_to_fill + 1 << std::endl << std::endl;
                grid[line][*it] = number_to_fill + 1;

                return true;
            }

        }

        // Reseting
        for (auto & found_number : found_numbers)
            found_number = 0;
             
    }
    return false;
}

// Can we fill the line with a missing number
bool can_fill_line(Grid & grid, const size_t line)
{
    std::vector<int>    numbers{ 1,2,3,4,5,6,7,8,9 };
    std::vector<int>    numbers_in_line;
    std::vector<int>    missing_numbers;
    std::vector<size_t> blank_columns;


    for (size_t column_check = 0; column_check < 9; ++column_check)
    {
        if (grid[line][column_check])
            numbers_in_line.push_back(grid[line][column_check]);
        else
            blank_columns.push_back(column_check);
    }

    std::sort(numbers_in_line.begin(), numbers_in_line.end());
    std::set_difference(numbers.begin(), numbers.end(),
        numbers_in_line.begin(), numbers_in_line.end(),
        std::back_inserter(missing_numbers));

    // We might have a chance to fill the line with a missing number on that line
    if (missing_numbers.size() == 1)
    {
        std::cout << "-!- Filled line " << line << " column " << blank_columns.front() << " with : " << missing_numbers.front() << std::endl << std::endl;
        grid[line][blank_columns.front()] = missing_numbers.front();
        return true;
    }
    else if (missing_numbers.size() == 2)
    {
        return try_to_fill_2blank_line(grid, line, missing_numbers, blank_columns);
    }
    else if (missing_numbers.size() == 3)
    {
        /*std::cout << "Missing numbers in line " << line << " : ";
        for (auto & number : missing_numbers)
            std::cout << number << " ";
        std::cout << std::endl;

        std::cout << "In maybe column : ";
        for (auto & blank_column : blank_columns)
            std::cout << blank_column << " ";
        std::cout << std::endl;*/

        return try_to_fill_3blank_line(grid, line, missing_numbers, blank_columns);
    }

    return false;
}