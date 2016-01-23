#include <sstream>
#include "point.h"

bool existline(std::stringstream const & ss)
{
    return ss.rdbuf()->in_avail();
}

std::ostream & operator<<(std::ostream& os, Point const & p)
{
    os << "{" << p.y << "," << p.x << "}";
    return os;
}
