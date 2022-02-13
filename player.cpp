#include <iostream>
#include "player.h"

Player::Player(int amountShips) //Player class constructor with the number of ships as an input
{
    ships = new Ship*[amountShips]; //declares an array of ship pointers equal to the number of ships

    /* LEE - Initialize each ship size to avoid seg fault*/
    for (int i = 0; i < amountShips; i++) //for each ship...
    {
        ships[i] = new Ship(i+1); //set the ship array value at i to a new instance of the ship class
    }

    numberOfShips = amountShips; //sets the int 'numerberOfShips' equal to the int 'amountShips'
}

Player::~Player(){ //Player class destructor
    for(int i=0; i< numberOfShips; i++){ //for each ship..
        delete ships[i]; //delete the ship at i
    }
    delete[] ships; //delete the array of ships
}

void Player::addShip(int shipNumber, int coordIndex, char xCoord, int yCoord, int shipSize)
{
    ships[shipNumber]->setXCoord(coordIndex, xCoord);
    ships[shipNumber]->setYCoord(coordIndex, yCoord);
}

void Player::getShipInfo(int shipNumber, int coordIndex) //player class function 'getShipInfo' requests the shipNumber in the array and the coordinate index
{
    char x;
    int y; 
    x = ships[shipNumber]->getXCoord(coordIndex); //sets int x to the x coordinate of the specified ship 
    y = ships[shipNumber]->getYCoord(coordIndex); //sets int y to the y coordinate of the specified ship
    std::cout << "[ADDED] Ship Number : " << shipNumber << ", Position : " << coordIndex << " at (" << x << " , " << y << ") has been added!" << std::endl; //outputs the relevant information
}


int Player::getPrevXCoord(int shipNumber, int coordIndex) //player class function 'getPrevXCoord' returns the previous x coordinate of the given ship number at the index
{
    return (int)ships[shipNumber]->getXCoord(coordIndex); //returns the x coordinate of the given ship number
}

int Player::getPrevYCoord(int shipNumber, int coordIndex) //player class function 'getPrevYCoord' returns the previous y coordinate of the given ship number at the index
{
    return ships[shipNumber]->getYCoord(coordIndex); //returns the y cooridnate of the given ship number
}

Ship* Player::getShip(int shipNumber) //player class function 'getShip' returns the corresponding ship class instance from the given ship number
{
    return ships[shipNumber]; //returns the ship class instance from the ship array at index shipNumber
}

bool Player::shipAttacked(char xGuess, int yGuess) //player class function 'shipAttacked' returns true if the given coordinates match the given coordinates of the ship
{
    for (int i = 0; i < numberOfShips; i++) // by ship index
    {
        int length = ships[i]->getShipLength(); //declares int 'length' and initializes with the value of the length of ship i

        for (int j = 0; j < length; j++) // by coord index
        {
            int xCoord = ships[i]->getXCoord(j); //declares int 'xCoord' and initializes with the value of ship i x coordinate
            int yCoord = ships[i]->getYCoord(j); //declares int 'yCoord' and initializes with the value of ship i y coordinate
            if ((xCoord == (int)xGuess) && (yCoord == yGuess)) // if x and y guesses are one of coord(ship(player))
            {
                ships[i]->positionAttacked(j); //sets the ships corresponding location to hit
                std::cout << "[DBG] - hit successful! ship: ID: " << i << " Position: " << j << std::endl; //outputs relevant information to the player

                int positionDownCount = 0; //declares int 'positionDownCount' initialized to 0
                for (int k = 0; k < length; k++) // check if the attack kills the ship
                {
                    if (ships[k]->positionDown(k)) //if the location on the ship was hit
                    {
                        positionDownCount++; //add one to positionDownCount
                        if(positionDownCount == length) //if the length of positionDownCount is equal to the length of the ship...
                        {
                            ships[i]->killShip(); //ship at the index is killed
                            std::cout << "[DBG] - Ship Down!" << std::endl; //player is informed that the ship is sunk
                        }
                    }
                }
                std::cout << std::endl; //creates new line
                return true; //returns true
            }
        }
    }
    std::cout << "[DBG] - not updated" << std::endl; //informs the player no ship was hit
    return false; //returns false
}

bool Player::allShipDown() //player class function 'allShipDown' checks if each ship in the array of ship classes is killed and returns a bool
{
    int shipDownCount = 0; //declares int 'shipDownCount' initialized to 0
    for (int i = 0; i < numberOfShips; i++) //for each ship...
    {
        if (ships[i]->isSank()) //if the ship is sunk
        {
            shipDownCount++; //increase shipDownCount by 1
        }
    }
    if (shipDownCount == numberOfShips) //if the number of ships down equals the number of ships...
    {
        return true; //returns true
    }
    return false; //returns false
}