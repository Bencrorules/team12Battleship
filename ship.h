#ifndef SHIP_H
#define SHIP_H

class Ship
{
    public:
    Ship(int length);
    bool isSank();
    void setXCoord(int spotNumber, char value);
    void setYCoord(int spotNumber, int value);

    private:
    int** shipCoords;
    bool* spotsHit;
    bool sank;
};
#endif
