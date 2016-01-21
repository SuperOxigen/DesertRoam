#include "map.h"
#include <iomanip>

using std::ostream;
using std::endl;
using std::setw;

Map::Map(size_t size):
    d_grid(size)
{
    for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < size; j++)
    {
        d_grid(i, j).reset(new DesertTile());
    }
}

size_t Map::size() const
{
    return d_grid.getM();
}

TilePtr & Map::operator()(size_t y, size_t x)
{
    return d_grid(y, x);
}

static void map_grid_full_line(ostream & os, size_t n)
{
    os << "+---";
    for (size_t i = 0; i < n; i++)
    {
        os << "+----";
    }
    os << "+";
}

static void map_grid_partial_line(ostream & os, size_t n)
{
    os << "|   ";
    for (size_t i = 0; i < n; i++)
    {
        os << "|    ";
    }
    os << "|";
}

ostream & operator<<(ostream & os, Map const & map)
{
    size_t size = map.size();

    for (size_t i = 0; i < size; i++)
    {
        map_grid_full_line(os, size);
        os << endl;
        map_grid_partial_line(os, size);
        os << endl;
        os << "|" << setw(2) << (i+1) << " ";
        for (size_t j = 0; j < size; j++)
        {
            os << "|" << " " << *(map.d_grid(i, j)) << " ";
        }
        os << "|" << endl;
        map_grid_partial_line(os, size);
        os << endl;
    }
    map_grid_full_line(os, size);
    os << endl;
    os << "|   ";
    for (size_t i = 0; i < size; i++)
    {
        os << "| " << setw(2) << (char) ('A' + i) << " ";
    }
    os << "|" << endl;
    map_grid_full_line(os, size);
    os << endl;

    return os;
}
