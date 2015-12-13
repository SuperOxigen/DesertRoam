#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include "inventory.h"

/*------------------------
 * Class: 
 * Description:
 *     
 *-----------------------*/
class Player {
    /*------------------------
     * Class:
     * Variable: 
     * Description:
     *     
     *-----------------------*/
    std::string d_name;

    /*------------------------
     * Class:
     * Variable: 
     * Description:
     *     
     *-----------------------*/
    Inventory d_inventory;

public:
    Player(std::string const &);

    Player(Player const &) = delete;
    Player(Player const &&) = delete;

    Player& operator=(Player const &) = delete;
    Player& operator=(Player const &&) = delete;

    friend std::ostream& operator<<(std::ostream&,Player const &);

    Inventory& inventory();
    std::string const & name() const;

    explicit operator bool() const;

    bool operator==(Player const &) const;
};

typedef std::shared_ptr<Player> PlayerPtr;


/*------------------------
 * Class: 
 * Description:
 *     
 *-----------------------*/
class PlayerSet
{
    /*------------------------
     * Class:
     * Variable: 
     * Description:
     *     
     *-----------------------*/
    std::vector<PlayerPtr> players;
public:
    PlayerSet();

    PlayerSet(PlayerSet const &) = delete;
    PlayerSet(PlayerSet const &&) = delete;

    PlayerSet& operator=(PlayerSet const &) = delete;
    PlayerSet& operator=(PlayerSet const &&) = delete;

    bool add_player(PlayerPtr);
    PlayerPtr get_player(std::string const &);
    PlayerPtr remove_player(std::string const &);
    std::vector<std::string> get_player_names() const;
};


