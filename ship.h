#ifndef SHIP_H
#define SHIP_H

class Ship
{
    public:
    Ship(int length);
    bool isSank();
    void setXCoord(int spotNumber, char value);
    char getXCoord(int spotNumber);
    void setYCoord(int spotNumber, int value);
    int getYCoord(int spotNumber);
    int getShipLength();
    void positionAttacked(int spotNumber);
    bool positionDown(int spotNumber);
    void killShip();


    private:
    int shipLength;
    int** shipCoords;
    bool* spotsHit;
    bool sank;
};
#endif
