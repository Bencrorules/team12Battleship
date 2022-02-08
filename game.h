#ifndef GAME_H
#define GAME_H
#include "player.h"

class Game
{
    public:
    Game();
    void playGame();
    void makeBoard();
    void printBoard();
    void obtainShips();
    int** board;
    int row;
    int col;
    int shipAmount;
    Player* player1;
    Player* player2;
};
#endif
