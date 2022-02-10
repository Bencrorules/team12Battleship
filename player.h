#ifndef PLAYER_H
#define PLAYER_H
#include "ship.h"

class Player
{
    public:
    Player(int amountShips);
    void addShip(int shipNumber, Ship* ship);

    private:
    Ship** ships;
};
#endif
