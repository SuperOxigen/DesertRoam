#pragma once

#include <iostream>

#include "tile.h"
#include "tile_factory.h"
#include "matrix.h"

typedef Matrix<TilePtr> TileGrid;

#define MAP_NO_HIGHLIGHT -1

class Map
{
    TileGrid d_grid;
    int d_hy, d_hx;
public:
    Map(size_t);
    Map(size_t, TileFactory&);
    
    TilePtr operator()(size_t, size_t) const;
    TilePtr operator*() const;
    size_t size() const;
    void highlight(int, int);
    void remove_highlight();

    friend std::ostream& operator<<(std::ostream &, Map const &);
};

