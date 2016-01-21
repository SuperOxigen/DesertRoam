#include "tile_factory.h"
#include <ctime>

TileFactory::TileFactory(size_t n):
    d_n(n), d_desert(DESERT_FRACTION), d_bandit(BANDIT_FRACTION),
    d_oasis(OASIS_FRACTION), d_store(STORE_FRACTION),
    d_gold_mine(GOLD_MINE_FRACTION), d_farm(FARM_FRACTION),
    d_home(HOME_FRACTION), d_market(MARKET_FRACTION),
    d_castle(CASTLE_FRACTION), d_total(TOTAL_WEIGHT) { }

TileFactory::TileFactory(size_t n, int weights[TILE_COUNT]):
    d_n(n), d_desert(weights[0]), d_bandit(weights[1]),
    d_oasis(weights[2]), d_store(weights[3]),
    d_gold_mine(weights[4]), d_farm(weights[5]),
    d_home(weights[6]), d_market(weights[7]),
    d_castle(weights[8]), d_total(0)
{
    for (size_t i = 0; i < TILE_COUNT; i++)
        d_total += weights[i];
}

TilePtr TileFactory::next()
{
    size_t weight(0);
    size_t value = rand() % d_total;

    if (d_n)
    {
        d_n--;
        if (value < (weight += d_desert))
            return TilePtr(new DesertTile());
        else if (value < (weight += d_bandit))
            return TilePtr(new BanditTile());
        else if (value < (weight += d_oasis))
            return TilePtr(new OasisTile());
        else if (value < (weight += d_store))
            return TilePtr(new StoreTile());
        else if (value < (weight += d_gold_mine))
            return TilePtr(new GoldMineTile());
        else if (value < (weight += d_farm))
            return TilePtr(new FarmTile());
        else if (value < (weight += d_home))
            return TilePtr(new HomeTile());
        else if (value < (weight += d_market))
            return TilePtr(new MarketTile());
        else if (value < (weight += d_castle))
            return TilePtr(new CastleTile());
        else
            return TilePtr(new DesertTile());
    }
    else
    {
        return TilePtr(new DesertTile());
    }
}
