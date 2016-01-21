#pragma once

#include <iostream>

struct Point
{
    int y, x;
};

extern std::ostream & operator<<(std::ostream& os, Point const & p);

