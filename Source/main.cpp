#include "Grid.h"
#include "Lines.h"
#include "Columns.h"
#include <iostream>


void printer(Grid & grid)
{
    for (size_t line = 0; line < 9; ++line)
    {
        for (size_t column = 0; column < 9; ++column)
        {
            std::cout << grid[line][column];
            if ((column + 1) % 3 == 0)
                std::cout << "|";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
        if ((line + 1) % 3 == 0)
            std::cout << "------------------" << std::endl;
    }
    std::cout << std::endl;
}


bool do_it(Grid & grid, const size_t & line, const size_t & column)
{
    if (grid[line][column] != 0)
    {
        std::cout << std ::endl << "CHECKING : [" << line << "][" << column << "] : " << grid[line][column] << std::endl;
        if (check_lines(grid, line, column) ||
            check_columns(grid, line, column))
            return true;
    }
    else
    {
        if (can_fill_line(grid, line) ||
            can_fill_column(grid, column))
            return true;
    }

    return false;
}

void checker(Grid & grid)
{
    for (size_t line = 0; line < 9; ++line)
    {
        for (size_t column = 0; column < 9; ++column)
        {
            if (do_it(grid, line, column) == true)
            {
                /*std::cout << "Here we go again ..." << std::endl;*/
                printer(grid);
                std::cout << std::endl;
                line = 0;
                column = 0;
            }
        }
    }
}

int main()
{
 
    Grid grid{
        // EASY 
         /*{ 4,0,0, 9,0,0, 0,5,0 },
         { 0,0,5, 6,0,7, 2,0,4 },
         { 0,0,0, 0,0,4, 7,0,0 },

         { 8,7,0, 3,0,0, 6,0,0 },
         { 0,0,9, 7,2,0, 1,8,0 },
         { 0,0,6, 8,9,1, 0,0,0 },

         { 1,0,2, 4,0,0, 5,6,8 },
         { 7,6,0, 5,3,8, 0,0,1 },
         { 0,0,8, 0,0,2, 0,7,0 }*/


        /* // MEDIUM
        { 0,0,5, 0,0,1, 0,0,0 },
        { 0,0,4, 3,2,6, 0,0,0 },
        { 8,0,0, 0,0,0, 1,9,3 },
    
        { 0,2,0, 0,4,0, 0,6,0 },
        { 9,0,0, 0,8,0, 0,0,4 },
        { 0,1,0, 0,7,0, 0,8,0 },

        { 5,4,7, 0,0,0, 0,0,2 },
        { 0,0,0, 2,3,7, 4,0,0 },
        { 0,0,0, 4,0,0, 9,0,0 }*/

        // HARD
        { 0,0,7, 0,5,3, 0,0,0 },
        { 0,0,4, 0,0,9, 0,2,5 },
        { 0,3,0, 0,4,0, 0,0,6 },

        { 0,0,8, 3,0,0, 0,0,7 },
        { 0,4,0, 0,0,0, 0,6,0 },
        { 7,0,0, 0,0,1, 8,0,0 },

        { 8,0,0, 0,6,0, 0,1,0 },
        { 1,7,0, 9,0,0, 4,0,0 },
        { 0,0,0, 5,1,0, 6,0,0 }
    };

    printer(grid);
    checker(grid);
    printer(grid);

    return(0);
}

