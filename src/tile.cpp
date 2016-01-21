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
        return true;
    }
    else
    {
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

string DesertTile::discription() const
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

string BanditTile::discription() const
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

string OasisTile::discription() const
{
    return string("A beautiful oasis, probably the only source of water around.");
}

string OasisTile::type_name() const
{
    return string(OASIS_NAME);
}
