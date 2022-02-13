#include <iostream>
#include "player.h"

Player::Player(int amountShips)
{
    ships = new Ship*[amountShips];

    /* LEE - Initialize each ship size to avoid seg fault*/
    for (int i = 0; i < amountShips; i++)
    {
        ships[i] = new Ship(i+1);
    }

    numberOfShips = amountShips;
}

Player::~Player(){
    for(int i=0; i< numberOfShips; i++){
        delete ships[i];
    }
    delete[] ships;
}

void Player::addShip(int shipNumber, int coordIndex, char xCoord, int yCoord, int shipSize)
{
    ships[shipNumber]->setXCoord(coordIndex, xCoord);
    ships[shipNumber]->setYCoord(coordIndex, yCoord);
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

Ship* Player::getShip(int shipNumber)
{
    return ships[shipNumber];
}

bool Player::shipAttacked(char xGuess, int yGuess)
{
    for (int i = 0; i < numberOfShips; i++) // by ship index
    {
        int length = ships[i]->getShipLength();

        for (int j = 0; j < length; j++) // by coord index
        {
            int xCoord = ships[i]->getXCoord(j);
            int yCoord = ships[i]->getYCoord(j);
            if ((xCoord == (int)xGuess) && (yCoord == yGuess)) // if x and y guesses are one of coord(ship(player))
            {
                ships[i]->positionAttacked(j);
                std::cout << "[DBG] - hit successful! ship: ID: " << i << " Position: " << j << std::endl;

                int positionDownCount = 0;
                for (int k = 0; k < length; k++) // check if the attack kills the ship
                {
                    if (ships[k]->positionDown(k))
                    {
                        positionDownCount++;
                        if(positionDownCount == length)
                        {
                            ships[i]->killShip();
                            std::cout << "[DBG] - Ship Down!" << std::endl;
                        }
                    }
                }
                std::cout << std::endl;
                return true;
            }
        }
    }
    std::cout << "[DBG] - not updated" << std::endl;
    return false;
}

bool Player::allShipDown()
{
    int shipDownCount = 0;
    for (int i = 0; i < numberOfShips; i++)
    {
        if (ships[i]->isSank())
        {
            shipDownCount++;
        }
    }
    if (shipDownCount == numberOfShips)
    {
        return true;
    }
    return false;
}