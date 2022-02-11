#ifndef PLAYER_H
#define PLAYER_H
#include "ship.h"

class Player
{
    public:
    Player(int amountShips);
    void addShip(int shipNumber, Ship* ship);
    
    void addShip(int shipNumber, int coordIndex, char xCoord, int yCoord, int shipSize);
    void getShipInfo(int shipNumber, int coordIndex); // Temp line - Lee
    int getPrevXCoord(int shipNumber, int coordIndex);
    int getPrevYCoord(int shipNumber, int coordIndex);

    private:
    Ship** ships;
};
#endif
