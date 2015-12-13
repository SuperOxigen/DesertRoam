#include "player.h"

using std::string;
using std::vector;

/*
 * ****  ****  ****  ****  ****
 * 
 *       Player Definition
 * 
 * ****  ****  ****  ****  ****
 */

Player::Player(string const & name):
    d_name(name) {}

Inventory& Player::inventory() { return d_inventory; }

string const & Player::name() const
{
    return d_name;
}

Player::operator bool() const
{
    if (d_inventory[WATER])
        return true;
    else
        return false;
}

bool Player::operator==(Player const & player) const
{
    return (d_name == player.d_name && d_inventory == player.d_inventory);
}


/*
 * ****  ****  ****  ****  ****
 * 
 *     PlayerSet Definition
 * 
 * ****  ****  ****  ****  ****
 */

PlayerSet::PlayerSet() {} // Nothing to do.

bool PlayerSet::add_player(PlayerPtr new_player)
{
    if (get_player(new_player->name()))
    {
        return false; // Already contains the player
    } else {
        players.push_back(new_player);
        return true;
    }
}

PlayerPtr PlayerSet::get_player(string const & player_name)
{
    PlayerPtr player_ptr;
    for (auto it = players.begin(); it != players.end(); it++)
    {
        if ((*it)->name() == player_name)
        {
            player_ptr = *it;
            break;
        }
    }
    return player_ptr;
}

PlayerPtr PlayerSet::remove_player(string const & player_name)
{
    PlayerPtr player_ptr;
    for (auto it = players.begin(); it != players.end(); it++)
    {
        if ((*it)->name() == player_name)
        {
            player_ptr = *it;
            it = players.erase(it);
            break;
        }
    }
    return player_ptr;
}

vector<string> PlayerSet::get_player_names() const
{
    vector<string> names;
    for (auto it = players.begin(); it != players.end(); it++)
    {
        names.push_back((*it)->name());
    }
    return  names;
}

