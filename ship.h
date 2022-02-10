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


    private:
    int** shipCoords;
    bool* spotsHit;
    bool sank;
};
#endif
