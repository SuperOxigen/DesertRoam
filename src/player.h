#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include "inventory.h"
#include "stat_bar.h"
#include "attack.h"

#define PLAYER_BASE_HEALTH 10
#define PLAYER_BASE_NEXT_LVL_EXP 5
#define PLAYER_MAX_LEVEL 10

class Player;

typedef AttackSet<Player> PlayerAttacks;

/*------------------------
 * Class: Player
 * Description:
 *     Represents a player in the game.
 *     A player has a number of stats and
 *     a inventory.
 *-----------------------*/
class Player
{
    /*------------------------
     * Class: Player
     * Variable: d_name
     * Description:
     *     Player's name stored as a string.
     *-----------------------*/
    std::string d_name;

    /*------------------------
     * Class: Player
     * Variable: d_level
     * Description:
     *     Player's level.
     *-----------------------*/
    unsigned int d_level;

    /*------------------------
     * Class: Player
     * Variable: d_inventory
     * Description:
     *     Player's basic inventory.
     *-----------------------*/
    Inventory d_inventory;

    /*------------------------
     * Class: Player
     * Variable: d_health_bar
     * Description:
     *     Player's health bar.
     *-----------------------*/
    StatBar d_health_bar;

    /*------------------------
     * Class: Player
     * Variable: d_exp_bar
     * Description:
     *     Player's experience bar.
     *-----------------------*/
    StatBar d_exp_bar;

    /*------------------------
     * Class: Player
     * Variable: d_attacks
     * Description:
     *     A set of attacks that a player
     *     can do.  Needs to be unlocked.
     *-----------------------*/
    PlayerAttacks d_attacks;

public:
    Player(std::string const &, unsigned int = PLAYER_BASE_HEALTH);

    Player(Player const &) = delete;
    Player(Player &&) = delete;

    Player const & operator=(Player const &) = delete;
    Player const & operator=(Player &&) = delete;

    friend std::ostream& operator<<(std::ostream&,Player const &);

    Inventory& inventory();
    Inventory inventory() const;

    StatBar& health_bar();
    StatBar health_bar() const;

    StatBar& health();
    StatBar health() const;

    StatBar& exp_bar();
    StatBar exp_bar() const;

    void add_exp(unsigned int = 1);
    void levelup();

    unsigned int level() const;

    PlayerAttacks& attacks();
    PlayerAttacks attacks() const;

    std::string const & name() const;

    explicit operator bool() const;

    bool operator==(Player const &) const;
};

/*------------------------
 * Typedef:  PlayerPtr
 * Description:
 *     A smart pointer to a player
 *     object.  Expected to be used often.
 *-----------------------*/
typedef std::shared_ptr<Player> PlayerPtr;

/*------------------------
 * Class: PlayerSet
 * Description:
 *     Represents a set of players, stored as shared
 *     pointers for memory safety.  
 *-----------------------*/
class PlayerSet
{
    /*------------------------
     * Class: PlayerSet
     * Variable: players
     * Description:
     *     A vector list of all the player pointers.
     *-----------------------*/
    std::vector<PlayerPtr> players;
public:
    PlayerSet();

    PlayerSet(PlayerSet const &) = default;

    PlayerSet& operator=(PlayerSet const &) = default;

    unsigned int size() const;
    unsigned int count() const;
    bool add_player(PlayerPtr);
    bool operator+=(PlayerPtr);
    PlayerPtr get_player(std::string const &);
    PlayerPtr operator[](std::string const &);
    bool operator[](std::string const &) const;
    PlayerPtr remove_player(std::string const &);
    std::vector<std::string> get_player_names() const;
};

