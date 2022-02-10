#include <iostream>
#include "ship.h"

Ship::Ship(int length)
{
    shipCoords = new int*[length];
    spotsHit = new bool[length];
    for (int i = 0; i < length; i++)
    {
        shipCoords[i] = new int[2];
        spotsHit[i] = false;
    }
    sank = false;
}

bool Ship::isSank()
{
    return sank;
}

void Ship::setXCoord(int spotNumber, char value)
{
    shipCoords[spotNumber][0] = value;
}

char Ship::getXCoord(int spotNumber)
{
    return shipCoords[spotNumber][0];
}

void Ship::setYCoord(int spotNumber, int value)
{
    shipCoords[spotNumber][1] = value;
}

int Ship::getYCoord(int spotNumber)
{
    return shipCoords[spotNumber][1];
}

