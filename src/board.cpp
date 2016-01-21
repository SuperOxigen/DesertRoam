#include "board.h"

#include <sstream>
#include <iomanip>

using std::string;
using std::stringstream;
using std::ostream;
using std::endl;
using std::setw;
using std::left;

static Point rand_point(int, int);
extern bool existline(stringstream const &);

Board::Board():
    d_map(BOARD_MAP_SIZE), d_current_player(nullptr) { }

Board& Board::operator+=(PlayerPtr & player_ptr)
{
    if (!d_players[player_ptr->name()])
    {
        d_players += player_ptr;
        d_pos_map[player_ptr->name()] = rand_point(0, d_map.size() - 1);
        std::cout << d_pos_map[player_ptr->name()] << endl;
        if (!d_current_player)
            set_current(player_ptr);
    }

    return * this;
}

Board& Board::operator-=(PlayerPtr & player_ptr)
{
    return * this -= player_ptr->name();
}

Board& Board::operator-=(string const & player_name)
{
    PlayerPtr temp_ptr;
    if (temp_ptr = d_players[player_name])
    {
        d_players.remove_player(player_name);
        d_pos_map.erase(player_name);
        if (temp_ptr == d_current_player || * temp_ptr == * d_current_player)
            set_current(PlayerPtr(nullptr));
    }

    return * this;
}

void Board::set_current(PlayerPtr player_ptr)
{
    if (!player_ptr)
    {
        d_current_player.reset();
        d_map.remove_highlight();
    }
    else if (d_players[player_ptr->name()])
    {
        d_current_player = player_ptr;
        Point p(d_pos_map[player_ptr->name()]);
        d_map.highlight(p.y, p.x);
    }
}

void Board::set_current(string const & player_name)
{
    set_current(d_players[player_name]);
}

PlayerPtr Board::get_current() const
{
    return d_current_player;
}

TilePtr Board::get_player_tile() const
{
    Point pos;
    if (get_current())
    {
        pos = d_pos_map.at(get_current()->name());
        return d_map(pos.y, pos.x);
    }
    else 
    {
        return TilePtr(nullptr);
    }
}

static void board_boarder_full(ostream & os, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        os << "-";
    }
    os << "+";
}

#define BOARD_PLAYER_WIDTH 20

ostream& operator<<(ostream & os, Board const & board)
{
    string map_line, player_line, tile_line;
    stringstream map_ss, player_ss, tile_ss;
    size_t width = 0;

    map_ss << board.d_map;
    if (board.get_current())
    {
        player_ss << * (board.get_current());
        tile_ss << board.get_player_tile()->type_name() << ": ";
        tile_ss << board.get_player_tile()->description();
    }

    while (existline(map_ss))
    {
        getline(map_ss, map_line);
        if (existline(player_ss) && width)
            getline(player_ss, player_line);
        else
            player_line = "";

        os << map_line;

        if (width == 0 && existline(map_ss))
        {
            width = map_line.length() + BOARD_PLAYER_WIDTH - 1;
            board_boarder_full(os, BOARD_PLAYER_WIDTH);
        }
        else if (existline(map_ss))
        {
            os << setw(BOARD_PLAYER_WIDTH) << left << player_line << "|";
        }

        if (existline(map_ss))
        {
            os << endl;
        }
        else
        {
            board_boarder_full(os, BOARD_PLAYER_WIDTH);
        }
    }

    if (board.get_current())
    {
        os << endl;
        getline(tile_ss, tile_line);
        os << "|";
        os << setw(width) << " " << "|" << endl;
        os << "|  " << setw(width - 2) << tile_line << "|" << endl;
        os << "|" << setw(width) << " " << "|" << endl;
        os << "+";
        board_boarder_full(os, width);
    }

    return os;
}

static Point rand_point(int min, int max)
{
    int y, x;
    y = (rand() % (max - min + 1)) + min;
    x = (rand() % (max - min + 1)) + min;

    return Point {y, x};
}
