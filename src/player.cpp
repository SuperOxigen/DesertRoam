#include "player.h"
#include <sstream>

using std::string;
using std::stringstream;
using std::vector;
using std::ostream;
using std::endl;

extern bool existline(stringstream const &);

/*
 * ****  ****  ****  ****  ****
 * 
 *       Player Definition
 * 
 * ****  ****  ****  ****  ****
 */

Player::Player(string const & name, unsigned int health):
    d_name(name), d_level(1), d_health_bar(health),
    d_exp_bar(0, PLAYER_BASE_NEXT_LVL_EXP) {}

Inventory& Player::inventory() { return d_inventory; }
Inventory Player::inventory() const { return d_inventory; }

StatBar& Player::health_bar() { return d_health_bar; }
StatBar Player::health_bar() const { return d_health_bar; }

StatBar& Player::health() { return d_health_bar; }
StatBar Player::health() const { return d_health_bar; }

StatBar& Player::exp_bar() { return d_exp_bar; }
StatBar Player::exp_bar() const { return d_exp_bar; }

void Player::add_exp(unsigned int exp)
{
    exp_bar() += exp;
    if (exp_bar().is_full())
        levelup();
}

void Player::levelup()
{
    if (d_level == PLAYER_MAX_LEVEL)
        return;
    d_level++;

    if (d_attacks.melee() && d_attacks.melee()->get_level() < d_level)
        d_attacks.melee()->levelup();

    if (d_attacks.range() && d_attacks.range()->get_level() < d_level)
        d_attacks.range()->levelup();    

    if (d_attacks.heal() && d_attacks.heal()->get_level() < d_level)
        d_attacks.heal()->levelup();

    d_exp_bar.set_max_value(d_level*PLAYER_BASE_NEXT_LVL_EXP);

    if (d_level == PLAYER_MAX_LEVEL)
        d_exp_bar.fill();
}

unsigned int Player::level() const { return d_level; }

string const & Player::name() const { return d_name; }

Player::operator bool() const
{
    if (d_inventory[WATER])
        return true;
    else
        return false;
}

/*------------------------
 * Class: Player
 * Operator: Equal Comparison
 * Parameters: const Player reference
 * Returns: true if the same player, false otherwise
 * Description:
 *     Compares all the attributes of the player class
 *     to check if the player two player classes are 
 *     the same.
 *-----------------------*/
bool Player::operator==(Player const & player) const
{
    return (d_name == player.d_name &&
            d_inventory == player.d_inventory &&
            d_health_bar == player.d_health_bar);
}

ostream& operator<<(ostream& os, Player const & player)
{
    stringstream ss;
    string line;
    StatBar health_bar(player.health_bar());
    StatBar exp_bar(player.exp_bar());
    health_bar.set_bar_type(StatBar::SMALL);
    exp_bar.set_bar_type(StatBar::SMALL);

    os << "Name: " << player.name() << endl;
    os << "LVL: " << player.level() << endl;
    os << "HP: " << health_bar << endl;
    os << "XP: " << exp_bar << endl;
    os << "Inventory:" << endl;
    
    ss << player.inventory();

    while (existline(ss))
    {
        getline(ss, line);
        os << "  " << line;
        if (existline(ss)) os << endl;
    }

    // while (ss)
    // {
    //     getline(ss, line);
    //     os << "  " << line;
    //     if (ss) os << endl;
    // }

    return os;
}


/*
 * ****  ****  ****  ****  ****
 * 
 *     PlayerSet Definition
 * 
 * ****  ****  ****  ****  ****
 */

PlayerSet::PlayerSet() {} // Nothing to do.

unsigned int PlayerSet::size() const
{
    return players.size();
}

unsigned int PlayerSet::count() const
{
    return size();
}


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

bool PlayerSet::operator+=(PlayerPtr new_player)
{
    return this->add_player(new_player);
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

PlayerPtr PlayerSet::operator[](string const & player_name)
{
    return this->get_player(player_name);
}

bool PlayerSet::operator[](string const & player_name) const
{
    PlayerPtr player_ptr;
    for (auto it = players.cbegin(); it != players.cend(); it++)
    {
        if ((*it)->name() == player_name)
        {
            player_ptr = *it;
            break;
        }
    }
    return !!player_ptr;
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

