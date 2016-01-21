#pragma once

#include <iostream>

#include "tile.h"
#include "tile_factory.h"
#include "matrix.h"

typedef Matrix<TilePtr> TileGrid;

class Map
{
    TileGrid d_grid;
public:
    Map(size_t);
    Map(size_t, TileFactory&);
    
    TilePtr & operator()(size_t, size_t);
    size_t size() const;

    friend std::ostream& operator<<(std::ostream &, Map const &);
};

