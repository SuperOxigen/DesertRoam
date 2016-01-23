#include "map.h"
#include <iomanip>

using std::ostream;
using std::endl;
using std::setw;

Map::Map(size_t size):
    d_grid(size), d_hy(MAP_NO_HIGHLIGHT), d_hx(MAP_NO_HIGHLIGHT)
{
    TileFactory tf(size * size);
    for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < size; j++)
    {
        d_grid(i, j) = tf.next();
    }
}

Map::Map(size_t size, TileFactory& tf):
    d_grid(size), d_hy(MAP_NO_HIGHLIGHT), d_hx(MAP_NO_HIGHLIGHT)
{
    for (size_t i = 0; i < size; i++)
    for (size_t j = 0; j < size; j++)
    {
        d_grid(i, j) = tf.next();
    }
}

size_t Map::size() const
{
    return d_grid.getM();
}

TilePtr Map::operator()(size_t y, size_t x) const
{
    if (d_grid.inBound(y,x))
        return d_grid(y, x);
    else
        return TilePtr(nullptr);
}

TilePtr Map::operator *() const
{
    if (d_hy != MAP_NO_HIGHLIGHT && d_hx != MAP_NO_HIGHLIGHT)
        return d_grid(d_hy, d_hx);
    else
        return TilePtr(nullptr);
}

void Map::highlight(int y, int x)
{
    if (d_grid.inBound(y,x))
    {
        d_hy = y;
        d_hx = x;
    }
}

void Map::remove_highlight()
{
    d_hy = d_hx = MAP_NO_HIGHLIGHT;
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
            if (map.d_hy == (int) i && map.d_hx == (int) j)
                os << "|" << "[" << *(map.d_grid(i, j)) << "]";
            else
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

    return os;
}


