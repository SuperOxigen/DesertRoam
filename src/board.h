#pragma once

#include <iostream>
#include <map>
#include <string>

#include "map.h"
#include "player.h"
#include "point.h"

typedef std::map<std::string, Point> PositionMap;

#define BOARD_MAP_SIZE 10

class Board
{
    Map d_map;
    PlayerPtr d_current_player;
    PlayerSet d_players;
    PositionMap d_pos_map;

    void set_current(PlayerPtr);

public:
    Board();

    Board& operator+=(PlayerPtr&);
    Board& operator-=(PlayerPtr&);
    Board& operator-=(std::string const &);

    void set_current(std::string const &);
    PlayerPtr get_current() const;
    TilePtr get_player_tile() const;

    friend std::ostream & operator<<(std::ostream&, Board const &);
};

