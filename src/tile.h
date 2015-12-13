#pragma once

#include "player.h"

/*------------------------
 * Constant: 
 * Description:
 *     
 *-----------------------*/
#define MAX_CHAR 2

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
    char symbol[MAX_CHAR+1];  // Extra char for string terminator
public:
    Tile();
    virtual bool can_move(Player const &) const = 0;
    virtual bool perform_action(Player &, PlayerSet &) = 0;
    virtual bool move_player(Player &) = 0;
};

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
    virtual bool can_move(Player const &) const;
    virtual bool perform_action(Player &, PlayerSet &);
    virtual bool move_player(Player &);
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
    virtual bool can_move(Player const &) const;
    virtual bool perform_action(Player &, PlayerSet &);
    virtual bool move_player(Player &);
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
    virtual bool can_move(Player const &) const;
    virtual bool perform_action(Player &, PlayerSet &);
    virtual bool move_player(Player &);
};

/*------------------------
 * Class: 
 * SuperClass: 
 * Description:
 *     
 *-----------------------*/
class ShopTile : public Tile
{
public:
    ShopTile();
    virtual bool can_move(Player const &) const;
    virtual bool perform_action(Player &, PlayerSet &);
    virtual bool move_player(Player &);
};

/*------------------------
 * Class: 
 * SuperClass: 
 * Description:
 *     
 *-----------------------*/
class GoldMineTile : public Tile
{
public:
    GoldMineTile();
    virtual bool can_move(Player const &) const;
    virtual bool perform_action(Player &, PlayerSet &);
    virtual bool move_player(Player &);
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
    virtual bool can_move(Player const &) const;
    virtual bool perform_action(Player &, PlayerSet &);
    virtual bool move_player(Player &);
};

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
    PlayerPtr owner;

    /*------------------------
     * Class:
     * Variable: 
     * Description:
     *     
     *-----------------------*/
    Inventory inventory;
public:
    HomeTile();
    virtual bool can_move(Player const &) const;
    virtual bool perform_action(Player &, PlayerSet &);
    virtual bool move_player(Player &);
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
    PlayerSet banned_players;

    /*------------------------
     * Class:
     * Variable: 
     * Description:
     *     
     *-----------------------*/
    Inventory inventory;
public:
    MarketTile();
    virtual bool can_move(Player const &) const;
    virtual bool perform_action(Player &, PlayerSet &);
    virtual bool move_player(Player &);
};

/*------------------------
 * Enum:  
 * Description:
 *     
 *-----------------------*/
enum KingType { NICE, MEAN, PASSIVE, GREEDY };

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
    KingType king_type;
public:
    CastleTile();
    virtual bool can_move(Player const &) const;
    virtual bool perform_action(Player &, PlayerSet &);
    virtual bool move_player(Player &);
};
