#include <iostream>
#include "player.h"

Player::Player(int amountShips)
{
    ships = new Ship*[amountShips];
}
