#ifndef SHIP_H
#define SHIP_H

class Ship
{
    public:
    Ship(int length);
    bool isSank();

    private:
    int** shipCoords;
    bool sank;
};
#endif
