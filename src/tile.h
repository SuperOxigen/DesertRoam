#pragma once

#include <iostream>
#include <string>
#include "player.h"
#include "tile_action.h"

/*------------------------
 * Constant: 
 * Description:
 *     
 *-----------------------*/
#define MAX_SYMBOL_CHAR 2

#define TILE_COUNT 9

#define DESERT_SYMBOL (char *) "D"
#define BANDIT_SYMBOL (char *) "B"
#define OASIS_SYMBOL  (char *) "O"
#define STORE_SYMBOL   (char *) "Sh"
#define GOLD_MINE_SYMBOL (char *) "GM"
#define FARM_SYMBOL   (char *) "F"
#define HOME_SYMBOL   (char *) "H"
#define MARKET_SYMBOL (char *) "M"
#define CASTLE_SYMBOL (char *) "C"

#define DESERT_NAME "Desert"
#define BANDIT_NAME "Bandit"
#define OASIS_NAME  "Oasis"
#define STORE_NAME  "Store"
#define GOLD_MINE_NAME "Gold mine"
#define FARM_NAME   "Farm"
#define HOME_NAME   "House"
#define MARKET_NAME "Market"
#define CASTLE_NAME "Castle"

#define NO_MESSAGE "No message"

/*------------------------
 * Class: 
 * Description:
 *     
 *-----------------------*/
class Tile
{
protected:
    /*------------------------
     * Class:
     * Variable: 
     * Description:
     *     
     *-----------------------*/
    char d_symbol[MAX_SYMBOL_CHAR+1];  // Extra char for string terminator

    std::string d_message;
public:
    Tile(char *);
    Tile(Tile const &);
    virtual Tile * clone() const = 0;
    virtual bool can_move(Player const &) const;
    virtual bool move_player(Player &);
    virtual bool has_action() const; // Default true
    virtual TileActionPtr get_action(Player &, PlayerSet &) = 0;

    virtual std::string const & get_message() const;
    virtual std::string description() const = 0;
    virtual std::string type_name() const = 0;

    friend std::ostream& operator<<(std::ostream&, Tile const &);
};

/*------------------------
 * Typedef:  
 * Description:
 *     
 *-----------------------*/
typedef std::shared_ptr<Tile> TilePtr;

/*------------------------
 * Class: 
 * SuperClass: 
 * Description:
 *     
 *-----------------------*/
class DesertTile : public Tile
{
public:
    DesertTile();
    DesertTile(DesertTile const &);
    virtual Tile * clone() const;
    virtual bool can_move(Player const &) const;
    virtual bool move_player(Player &);
    virtual bool has_action() const;
    virtual TileActionPtr get_action(Player &, PlayerSet &);
    virtual std::string description() const;
    virtual std::string type_name() const;
};

/*------------------------
 * Class: 
 * SuperClass: 
 * Description:
 *     
 *-----------------------*/
class BanditTile : public Tile
{
public:
    BanditTile();
    BanditTile(BanditTile const &);
    virtual Tile * clone() const;
    virtual bool can_move(Player const &) const;
    virtual bool move_player(Player &);
    virtual TileActionPtr get_action(Player &, PlayerSet &);
    virtual std::string description() const;
    virtual std::string type_name() const;
};

/*------------------------
 * Class: 
 * SuperClass: 
 * Description:
 *     
 *-----------------------*/
class OasisTile : public Tile
{
public:
    OasisTile();
    OasisTile(OasisTile const &);
    virtual Tile * clone() const;
    virtual bool can_move(Player const &) const;
    virtual bool move_player(Player &);
    virtual TileActionPtr get_action(Player &, PlayerSet &);
    virtual std::string description() const;
	virtual std::string type_name() const;
};

/*------------------------
 * Class: 
 * SuperClass: 
 * Description:
 *     
 *-----------------------*/
class StoreTile : public Tile
{
public:
    StoreTile();
    StoreTile(StoreTile const &);
    virtual Tile * clone() const;
    virtual bool can_move(Player const &) const;
    virtual bool move_player(Player &);
    virtual TileActionPtr get_action(Player &, PlayerSet &);
    virtual std::string description() const;
	virtual std::string type_name() const;
};

/*------------------------
 * Constant: 
 * Description:
 *     
 *-----------------------*/
#define GOLD_MINE_MAX_GOLD 100

/*------------------------
 * Class: 
 * SuperClass: 
 * Description:
 *     
 *-----------------------*/
class GoldMineTile : public Tile
{
    /*------------------------
     * Class:
     * Variable: 
     * Description:
     *     
     *-----------------------*/
    unsigned int d_gold_reserves;
public:
    GoldMineTile();
    GoldMineTile(GoldMineTile const &);
    virtual Tile * clone() const;
    virtual bool can_move(Player const &) const;
    virtual bool move_player(Player &);
    virtual TileActionPtr get_action(Player &, PlayerSet &);
    virtual std::string description() const;
	virtual std::string type_name() const;
};

/*------------------------
 * Class: 
 * SuperClass: 
 * Description:
 *     
 *-----------------------*/
class FarmTile : public Tile
{
public:
    FarmTile();
    FarmTile(FarmTile const &);
    virtual Tile * clone() const;
    virtual bool can_move(Player const &) const;
    virtual bool move_player(Player &);
    virtual TileActionPtr get_action(Player &, PlayerSet &);
    virtual std::string description() const;
	virtual std::string type_name() const;
};

#define HOME_TILE_PRICE_MIN 15
#define HOME_TILE_PRICE_MAX 5

/*------------------------
 * Class: 
 * SuperClass: 
 * Description:
 *     
 *-----------------------*/
class HomeTile : public Tile
{
    /*------------------------
     * Class:
     * Variable: 
     * Description:
     *     
     *-----------------------*/
    PlayerPtr d_owner;

    /*------------------------
     * Class:
     * Variable: 
     * Description:
     *     
     *-----------------------*/
    Inventory d_inventory;

    /*------------------------
     * Class:
     * Variable: 
     * Description:
     *     
     *-----------------------*/
    unsigned int d_price;
public:
    HomeTile();
    HomeTile(HomeTile const &);
    virtual Tile * clone() const;
    virtual bool can_move(Player const &) const;
    virtual bool move_player(Player &);
    virtual TileActionPtr get_action(Player &, PlayerSet &);
    virtual std::string description() const;
	virtual std::string type_name() const;
};

/*------------------------
 * Class: 
 * SuperClass: 
 * Description:
 *     
 *-----------------------*/
class MarketTile : public Tile
{
    /*------------------------
     * Class:
     * Variable: 
     * Description:
     *     
     *-----------------------*/
    PlayerSet d_banned_players;

    /*------------------------
     * Class:
     * Variable: 
     * Description:
     *     
     *-----------------------*/
    Inventory d_inventory;
public:
    MarketTile();
    MarketTile(MarketTile const &);
    virtual Tile * clone() const;
    virtual bool can_move(Player const &) const;
    virtual bool move_player(Player &);
    virtual TileActionPtr get_action(Player &, PlayerSet &);
    virtual std::string description() const;
	virtual std::string type_name() const;
};

/*------------------------
 * Enum:  
 * Description:
 *     
 *-----------------------*/
enum KingType { NICE, MEAN, PASSIVE, GREEDY };

#define NUM_KING_TYPES 4

/*------------------------
 * Class: 
 * SuperClass: 
 * Description:
 *     
 *-----------------------*/
class CastleTile : public Tile
{
    /*------------------------
     * Class:
     * Variable: 
     * Description:
     *     
     *-----------------------*/
    KingType d_king_type;
public:
    CastleTile();
    CastleTile(CastleTile const &);
    virtual Tile * clone() const;
    virtual bool can_move(Player const &) const;
    virtual bool move_player(Player &);
    virtual TileActionPtr get_action(Player &, PlayerSet &);
    virtual std::string description() const;
	virtual std::string type_name() const;
};
