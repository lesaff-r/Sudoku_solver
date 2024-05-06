#pragma once

#include "Grid.h"

bool    check_columns   (Grid & grid, const size_t & line, const size_t & column);
bool    can_fill_column (Grid & grid, const size_t column);