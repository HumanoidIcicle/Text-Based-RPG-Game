#include <iostream>
#include "Player.h"
#include "Game.h"

using namespace std;

int main() {
    Game g;
    Player p;
    int turns = 0;
    bool yourTurn = true;

    g.initializeWorld(&p);
    g.youPlaying(true, turns, yourTurn);

    return 0;
}
