#ifndef GAME_H
#define GAME_H
#include "player.h"

class Game
{
    public:
    Game();
    ~Game();
    void playGame();
    void makeBoard();
    void printBoard();
    void obtainShips();
    void playerGuess();
    void labels();
    void finishGame(int playerID);
    int** board;
    int row = 11;
    int col = 11;
    int shipAmount;
    bool gameFinished = false;
    Player* player1;
    Player* player2;
};
#endif
