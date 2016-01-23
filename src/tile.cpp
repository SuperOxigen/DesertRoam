#include <cstring>
#include <iomanip>
#include "tile.h"
#include "resource.h"

using std::string;
using std::ostream;
using std::setw;

/*
 * ****  ****  ****  ****  ****
 * 
 *       Tile Definition
 * 
 * ****  ****  ****  ****  ****
 */

Tile::Tile(char * symbol):
    d_message(NO_MESSAGE)
{
    strncpy(d_symbol, symbol, MAX_SYMBOL_CHAR);
    d_symbol[MAX_SYMBOL_CHAR] = 0;
}

Tile::Tile(Tile const & tile):
    d_message(tile.d_message)
{
    strncpy(d_symbol, tile.d_symbol, MAX_SYMBOL_CHAR);
    d_symbol[MAX_SYMBOL_CHAR] = 0;
}

bool Tile::can_move(Player const & player) const
{
    return player.inventory()[WATER] && player.inventory()[FOOD];
}

bool Tile::move_player(Player & player)
{
    if (can_move(player))
    {
        Inventory & inventory(player.inventory());
        inventory.set_resource(WATER, inventory.get_resource(WATER) - 1);
        inventory.set_resource(FOOD, inventory.get_resource(FOOD) - 1);
        d_message = NO_MESSAGE;
        return true;
    }
    else
    {
        d_message = "Not enough food and water.";
        return false;
    }
}

bool Tile::has_action() const { return true; }

string const & Tile::get_message() const
{
    return d_message;
}

ostream & operator<<(ostream & os, Tile const & tile)
{
    os << setw(MAX_SYMBOL_CHAR) << tile.d_symbol;
    return os;
}

/*
 * ****  ****  ****  ****  ****
 * 
 *    Desert Tile Definition
 * 
 * ****  ****  ****  ****  ****
 */

DesertTile::DesertTile():
    Tile(DESERT_SYMBOL) {}

DesertTile::DesertTile(DesertTile const & desert_tile):
    Tile(desert_tile) {}

Tile * DesertTile::clone() const
{
    return new DesertTile(* this);
}

bool DesertTile::can_move(Player const & player) const
{
    return Tile::can_move(player);
}

bool DesertTile::move_player(Player & player) 
{
    return Tile::move_player(player);
}

bool DesertTile::has_action() const { return false; }

TileActionPtr DesertTile::get_action(Player &, PlayerSet &)
{
    d_message = "Nothing to do here";
    return TileActionPtr(nullptr);
}

string DesertTile::description() const
{
    return string("Nothing to do, just walk...");
}

string DesertTile::type_name() const
{
    return string(DESERT_NAME);
}

/*
 * ****  ****  ****  ****  ****
 * 
 *    Bandit Tile Definition
 * 
 * ****  ****  ****  ****  ****
 */

BanditTile::BanditTile():
    Tile(BANDIT_SYMBOL) {}

BanditTile::BanditTile(BanditTile const & bandit_tile):
    Tile(bandit_tile) {}

Tile * BanditTile::clone() const
{
    return new BanditTile(* this);
}

bool BanditTile::can_move(Player const & player) const
{
    return Tile::can_move(player);
}

bool BanditTile::move_player(Player & player)
{
    return Tile::move_player(player);
}

TileActionPtr BanditTile::get_action(Player & player, PlayerSet&)
{
    return TileActionPtr(new BanditAction(player));
}

string BanditTile::description() const
{
    return string("Bandit camp, they may want something from you.");
}

string BanditTile::type_name() const
{
    return string(BANDIT_NAME);
}

/*
 * ****  ****  ****  ****  ****
 * 
 *    Oasis Tile Definition
 * 
 * ****  ****  ****  ****  ****
 */

OasisTile::OasisTile():
    Tile(OASIS_SYMBOL) {}

OasisTile::OasisTile(OasisTile const & oasis_tile):
    Tile(oasis_tile) {}

Tile * OasisTile::clone() const
{
    return new OasisTile(* this);
}

bool OasisTile::can_move(Player const & player) const
{
    return player.inventory()[FOOD];
}

bool OasisTile::move_player(Player & player)
{
    if (can_move(player))
    {
        Inventory & inventory(player.inventory());
        inventory.set_resource(FOOD, inventory.get_resource(FOOD) - 1);        
        return true;
    }
    else
    {
        return false;
    }
}

TileActionPtr OasisTile::get_action(Player & player, PlayerSet&)
{
    return TileActionPtr(new OasisAction(player));
}

string OasisTile::description() const
{
    return string("A beautiful oasis, probably the only source of water around.");
}

string OasisTile::type_name() const
{
    return string(OASIS_NAME);
}

/*
 * ****  ****  ****  ****  ****
 * 
 *    Store Tile Definition
 * 
 * ****  ****  ****  ****  ****
 */

StoreTile::StoreTile():
    Tile(STORE_SYMBOL) {}

StoreTile::StoreTile(StoreTile const & store_tile):
    Tile(store_tile) {}

Tile * StoreTile::clone() const
{
    return new StoreTile(* this);
}

bool StoreTile::can_move(Player const & player) const
{
    return Tile::can_move(player);
}

bool StoreTile::move_player(Player & player)
{
    return Tile::move_player(player);
}

TileActionPtr StoreTile::get_action(Player & player, PlayerSet&)
{
    return TileActionPtr(new StoreAction(player));
}

string StoreTile::description() const
{
    return string("A store, great place to buy seperatly needed items.");
}

string StoreTile::type_name() const
{
    return string(STORE_NAME);
}

/*
 * ****  ****  ****  ****  ****
 * 
 *    Gold Mine Tile Definition
 * 
 * ****  ****  ****  ****  ****
 */

GoldMineTile::GoldMineTile():
    Tile(GOLD_MINE_SYMBOL)
{
    d_gold_reserves = rand() % GOLD_MINE_MAX_GOLD;
}

GoldMineTile::GoldMineTile(GoldMineTile const & gold_mine_tile):
    Tile(gold_mine_tile), d_gold_reserves(gold_mine_tile.d_gold_reserves) {}

Tile * GoldMineTile::clone() const
{
    return new GoldMineTile(* this);
}

bool GoldMineTile::can_move(Player const & player) const
{
    return Tile::can_move(player);
}

bool GoldMineTile::move_player(Player & player)
{
    return Tile::move_player(player);
}

TileActionPtr GoldMineTile::get_action(Player & player, PlayerSet&)
{
    return TileActionPtr(new GoldMineAction(player, d_gold_reserves));
}

string GoldMineTile::description() const
{
    return string("A gold mine, might be able to make my fortune working there.");
}

string GoldMineTile::type_name() const
{
    return string(GOLD_MINE_NAME);
}

/*
 * ****  ****  ****  ****  ****
 * 
 *    Farm Tile Definition
 * 
 * ****  ****  ****  ****  ****
 */

FarmTile::FarmTile():
    Tile(FARM_SYMBOL) {}

FarmTile::FarmTile(FarmTile const & farm_tile):
    Tile(farm_tile) {}

Tile * FarmTile::clone() const
{
    return new FarmTile(* this);
}

bool FarmTile::can_move(Player const & player) const
{
    return Tile::can_move(player);
}

bool FarmTile::move_player(Player & player)
{
    return Tile::move_player(player);
}

TileActionPtr FarmTile::get_action(Player & player, PlayerSet&)
{
    return TileActionPtr(new FarmAction(player));
}

string FarmTile::description() const
{
    return string("A small farm land.  Maybe they will trade some food for work.");
}

string FarmTile::type_name() const
{
    return string(FARM_NAME);
}

/*
 * ****  ****  ****  ****  ****
 * 
 *    Home Tile Definition
 * 
 * ****  ****  ****  ****  ****
 */

HomeTile::HomeTile():
    Tile(HOME_SYMBOL), d_owner(PlayerPtr(nullptr)),
    d_inventory()
{
    for (int i = 0; i < NUM_RESOURCES; i++)
        d_inventory.set_capacity((ResourceType) i, d_inventory.get_capacity((ResourceType) i) * 3);
    d_price = (rand() % (HOME_TILE_PRICE_MAX - HOME_TILE_PRICE_MIN + 1)) + HOME_TILE_PRICE_MIN;
}

HomeTile::HomeTile(HomeTile const & home_tile):
    Tile(home_tile), d_owner(home_tile.d_owner),
    d_inventory(home_tile.d_inventory),
    d_price(home_tile.d_price) {}

Tile * HomeTile::clone() const
{
    return new HomeTile(* this);
}

bool HomeTile::can_move(Player const & player) const
{
    if (d_owner && * d_owner == player) // Player owns tile
    {
        return (player.inventory()[FOOD] + d_inventory[FOOD]) &&
                (player.inventory()[WATER] + d_inventory[WATER]);
    }
    else
    {
        return Tile::can_move(player);
    }
}

bool HomeTile::move_player(Player & player)
{    
    if (d_owner && * d_owner == player && can_move(player)) // Player owns tile
    {
        Inventory & inventory = player.inventory();
        if (d_inventory[FOOD])
            d_inventory.set_resource(FOOD, d_inventory.get_resource(FOOD) - 1);
        else
            inventory.set_resource(FOOD, inventory.get_resource(FOOD) - 1);

        if (d_inventory[WATER])
            d_inventory.set_resource(WATER, d_inventory.get_resource(WATER) - 1);
        else
            inventory.set_resource(WATER, inventory.get_resource(WATER) - 1);

        return true;
    }
    else
    {
        return Tile::move_player(player);
    }
}

TileActionPtr HomeTile::get_action(Player & player, PlayerSet&)
{
    if (d_owner && * d_owner == player)
        return TileActionPtr(new HomeOwnerAction(player, d_inventory));
    else if (d_owner)
        return TileActionPtr(new HomeVisitorAction(player));
    else
        return TileActionPtr(new HomeSaleAction(player, d_price));
}

string HomeTile::description() const
{
    return string("Home, a good place to store your goods.");
}

string HomeTile::type_name() const
{
    return string(HOME_NAME);
}

/*
 * ****  ****  ****  ****  ****
 * 
 *    Market Tile Definition
 * 
 * ****  ****  ****  ****  ****
 */

MarketTile::MarketTile():
    Tile(MARKET_SYMBOL)
{
    for (int i = 0; i < NUM_RESOURCES; i++)
    {
        d_inventory.set_capacity((ResourceType) i, d_inventory.get_capacity((ResourceType) i) * 3);
        d_inventory.set_resource((ResourceType) i, rand() % d_inventory.get_capacity((ResourceType) i));
    }
    d_inventory.set_capacity(GOLD, d_inventory.get_capacity(GOLD) * 4);
    d_inventory.set_resource(GOLD, rand() % d_inventory.get_capacity(GOLD));
}

MarketTile::MarketTile(MarketTile const & market_tile):
    Tile(market_tile), d_banned_players(market_tile.d_banned_players),
    d_inventory(market_tile.d_inventory) {}

Tile * MarketTile::clone() const
{
    return new MarketTile(* this);
}

bool MarketTile::can_move(Player const & player) const
{
    if (Tile::can_move(player))
    {
        if (!d_banned_players[player.name()])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool MarketTile::move_player(Player & player)
{
    return Tile::move_player(player);
}

TileActionPtr MarketTile::get_action(Player & player, PlayerSet&)
{
    return TileActionPtr(new MarketAction(player, d_inventory));
}

string MarketTile::description() const
{
    return string("A small market, great place to trade resources.");
}

string MarketTile::type_name() const
{
    return string(MARKET_NAME);
}

/*
 * ****  ****  ****  ****  ****
 * 
 *    Castle Tile Definition
 * 
 * ****  ****  ****  ****  ****
 */

CastleTile::CastleTile():
    Tile(CASTLE_SYMBOL)
{
    d_king_type = (KingType) (rand() % NUM_KING_TYPES);
}

CastleTile::CastleTile(CastleTile const & castle_tile):
    Tile(castle_tile), d_king_type(castle_tile.d_king_type) {}

Tile * CastleTile::clone() const
{
    return new CastleTile(* this);
}

bool CastleTile::can_move(Player const & player) const
{
    return Tile::can_move(player);
}

bool CastleTile::move_player(Player & player)
{
    return Tile::move_player(player);
}

TileActionPtr CastleTile::get_action(Player & player, PlayerSet&)
{
    switch (d_king_type)
    {
        case NICE:
            return TileActionPtr(new CastleNiceKingAction(player));
        case MEAN:
            return TileActionPtr(new CastleMeanKingAction(player));
        case PASSIVE:
            return TileActionPtr(new CastlePassiveKingAction(player));
        case GREEDY:
            return TileActionPtr(new CastleGreedyKingAction(player));
        default:
            return TileActionPtr(new CastleNoKingAction());
    }
}

string CastleTile::description() const
{
    return string("A king lives here, maybe he's nice.");
}

string CastleTile::type_name() const
{
    return string(CASTLE_NAME);
}

