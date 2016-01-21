#include "tile_action.h"

using std::ostream;
using std::istream;

BanditAction::BanditAction(Player & player):
    d_player(player) {}

bool BanditAction::execute(ostream& os, istream& is)
{


    return false;
}

OasisAction::OasisAction(Player& player):
    d_player(player) {}

bool OasisAction::execute(ostream& os, istream& is)
{
    return false;
}

ShopAction::ShopAction(Player& player):
    d_player(player) {}

bool ShopAction::execute(ostream& os, istream& is)
{
    return false;
}

GoldMineAction::GoldMineAction(Player& player):
    d_player(player) {}

bool GoldMineAction::execute(ostream& os, istream& is)
{
    return false;
}

FarmAction::FarmAction(Player& player):
    d_player(player) {}

bool FarmAction::execute(ostream& os, istream& is)
{
    return false;
}

HomeOwnerAction::HomeOwnerAction(Player& player, Inventory& inventory):
    d_player(player), d_inventory(inventory) {}

bool HomeOwnerAction::execute(ostream& os, istream& is)
{
    return false;
}

HomeSaleAction::HomeSaleAction(Player& player, unsigned int price):
    d_player(player), d_price(price) {}

bool HomeSaleAction::execute(ostream& os, istream& is)
{
    return false;
}

HomeVisitorAction::HomeVisitorAction(Player& player):
    d_player(player) {}

bool HomeVisitorAction::execute(ostream& os, istream& is)
{
    return false;
}

MarketAction::MarketAction(Player& player, Inventory& inventory):
    d_player(player), d_inventory(inventory) {}

bool MarketAction::execute(ostream& os, istream& is)
{
    return false;
}

CastleNiceKingAction::CastleNiceKingAction(Player& player):
    d_player(player) {}

bool CastleNiceKingAction::execute(ostream& os, istream& is)
{
    return false;
}

CastleMeanKingAction::CastleMeanKingAction(Player& player):
    d_player(player) {}

bool CastleMeanKingAction::execute(ostream& os, istream& is)
{
    return false;
}

CastlePassiveKingAction::CastlePassiveKingAction(Player& player):
    d_player(player) {}

bool CastlePassiveKingAction::execute(ostream& os, istream& is)
{
    return false;
}

CastleGreedyKingAction::CastleGreedyKingAction(Player& player):
    d_player(player) {}

bool CastleGreedyKingAction::execute(ostream& os, istream& is)
{
    return false;
}

CastleNoKingAction::CastleNoKingAction() {}

bool CastleNoKingAction::execute(ostream& os, istream& is)
{
    return false;
}
