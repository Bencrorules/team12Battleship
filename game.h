#ifndef GAME_H
#define GAME_H

class Game
{
public:
    void makeBoard();
    void printBoard(int **arr);
    void boardBuild();
    int **board;
    int row = 10;
    int col = 10;
};
#endif
