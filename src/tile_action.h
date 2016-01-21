#pragma once

#include <iostream>
#include <memory>
#include "player.h"
#include "inventory.h"

class TileAction
{
public:
    virtual bool execute(std::ostream &, std::istream &) = 0;
};

typedef std::shared_ptr<TileAction> TileActionPtr;

class BanditAction : public TileAction
{
    Player& d_player;
public:
    BanditAction(Player&);
    virtual bool execute(std::ostream &, std::istream &);
};

class OasisAction : public TileAction
{
    Player& d_player;
public:
    OasisAction(Player&);
    virtual bool execute(std::ostream &, std::istream &);
};

class ShopAction : public TileAction
{
    Player& d_player;
public:
    ShopAction(Player&);
    virtual bool execute(std::ostream &, std::istream &);
};

class GoldMineAction : public TileAction
{
    Player& d_player;
public:
    GoldMineAction(Player&);
    virtual bool execute(std::ostream &, std::istream &);
};

class FarmAction : public TileAction
{
    Player& d_player;
public:
    FarmAction(Player&);
    virtual bool execute(std::ostream &, std::istream &);
};

class HomeOwnerAction : public TileAction
{
    Player& d_player;
    Inventory& d_inventory;
public:
    HomeOwnerAction(Player&, Inventory&);
    virtual bool execute(std::ostream &, std::istream &);    
};

class HomeSaleAction : public TileAction
{
    Player& d_player;
    unsigned int d_price;
public:
    HomeSaleAction(Player&, unsigned int);
    virtual bool execute(std::ostream &, std::istream &);
};

class HomeVisitorAction : public TileAction
{
    Player& d_player;
public:
    HomeVisitorAction(Player&);
    virtual bool execute(std::ostream &, std::istream &);
};

class MarketAction : public TileAction
{
    Player& d_player;
    Inventory& d_inventory;
public:
    MarketAction(Player&, Inventory&);
    virtual bool execute(std::ostream &, std::istream &);
};

class CastleNiceKingAction : public TileAction
{
    Player& d_player;
public:
    CastleNiceKingAction(Player&);
    virtual bool execute(std::ostream &, std::istream &);
};

class CastleMeanKingAction : public TileAction
{
    Player& d_player;
public:
    CastleMeanKingAction(Player&);
    virtual bool execute(std::ostream &, std::istream &);
};

class CastlePassiveKingAction : public TileAction
{
    Player& d_player;
public:
    CastlePassiveKingAction(Player&);
    virtual bool execute(std::ostream &, std::istream &);
};

class CastleGreedyKingAction : public TileAction
{
    Player& d_player;
public:
    CastleGreedyKingAction(Player&);
    virtual bool execute(std::ostream &, std::istream &);
};

class CastleNoKingAction : public TileAction
{
public:
    CastleNoKingAction();
    virtual bool execute(std::ostream &, std::istream &);
};

