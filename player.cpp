#include <iostream>
#include "player.h"

Player::Player(int amountShips)
{
    ships = new Ship*[amountShips];
}

/* Add ship information to a Players ship collection */
void Player::addShip(int shipNumber, Ship* ship)
{

}

/* temp function - Lee  */
void Player::addShip(int shipNumber, int coordIndex, char xCoord, int yCoord, int shipSize)
{
    Ship* tempShip = new Ship(shipSize);
    tempShip->setXCoord(coordIndex, xCoord);
    tempShip->setYCoord(coordIndex, yCoord);

    ships[shipNumber] = tempShip;
}

void Player::getShipInfo(int shipNumber, int coordIndex)
{
    int x,y;
        x = ships[shipNumber]->getXCoord(coordIndex);
        y = ships[shipNumber]->getYCoord(coordIndex);
        std::cout << "[DBG] Ship Index : " << shipNumber << ", Coord Index : " << coordIndex << " :: coord :: " << x << " , " << y << std::endl;
}

int Player::getPrevXCoord(int shipNumber, int coordIndex)
{
    return (int)ships[shipNumber]->getXCoord(coordIndex);
}

int Player::getPrevYCoord(int shipNumber, int coordIndex)
{
    return ships[shipNumber]->getYCoord(coordIndex);
}