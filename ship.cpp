#include <iostream>
#include "ship.h"

Ship::Ship(int length)
{
    shipLength = length;
    shipCoords = new int*[length];
    spotsHit = new bool[length];
    for (int i = 0; i < length; i++)
    {
        shipCoords[i] = new int[2];
        spotsHit[i] = false;
    }
    sank = false;
    /* Initialize coord values to avoid seg fault */
    for (int i = 0; i < length; i++)
    {
        shipCoords[i][0] = 0;
        shipCoords[i][1] = 0;
    }
}

Ship::~Ship(){
    delete[] spotsHit;
    for(int i=0; i<shipLength; i++){
        delete[] shipCoords[i];
    }
    delete[] shipCoords;
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

int Ship::getShipLength()
{
    return shipLength;
}

void Ship::positionAttacked(int spotNumber)
{
    spotsHit[spotNumber] = true;
}

bool Ship::positionDown(int spotNumber)
{
    if (spotsHit[spotNumber] == true)
    {
        return true;
    }
    return false;
}

void Ship::killShip()
{
    sank = true;
}