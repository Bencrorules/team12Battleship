#include <iostream>
#include "ship.h"

Ship::Ship(int length)
{
    shipCoords = new int*[length];
    for (int i = 0; i < length; i++)
    {
        shipCoords[i] = new int[2];
    }
    sank = false;
}

bool Ship::isSank()
{
    return sank;
}
