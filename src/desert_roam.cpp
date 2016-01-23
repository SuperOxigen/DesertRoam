#include "player.h"
#include "board.h"
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::stringstream;
using std::string;

static void init()
{
    srand(time(NULL));
}

int main(void)
{
    init();
    PlayerPtr pl(new Player("Alex"));
    AttackPtr attack(new MeleeAttack<Player>());

    Board board;
    board += pl;

    cout << board << endl;

    return 0;
}

