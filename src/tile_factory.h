#pragma once

#include "tile.h"

#define DESERT_FRACTION 50
#define BANDIT_FRACTION 3
#define OASIS_FRACTION 8
#define STORE_FRACTION 3
#define GOLD_MINE_FRACTION 12
#define FARM_FRACTION 12
#define HOME_FRACTION 3
#define MARKET_FRACTION 5
#define CASTLE_FRACTION 4

#define TOTAL_WEIGHT (DESERT_FRACTION + BANDIT_FRACTION    + OASIS_FRACTION \
                    + STORE_FRACTION  + GOLD_MINE_FRACTION + FARM_FRACTION \
                    + HOME_FRACTION   + MARKET_FRACTION    + CASTLE_FRACTION)

class TileFactory
{
    size_t d_n;

    int d_desert,   d_bandit,   d_oasis,
        d_store,    d_gold_mine,d_farm,
        d_home,     d_market,   d_castle;

    size_t d_total;

public:
    TileFactory(size_t n);
    TileFactory(size_t, int [TILE_COUNT]);

    TilePtr next();
};
