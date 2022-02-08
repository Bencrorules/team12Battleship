#ifndef PLAYER_H
#define PLAYER_H
#include "ship.h"

class Player
{
    public:
    Player(int amountShips);
    Ship** ships;
};
#endif
