#include <iostream>
#include <charconv>
#include "game.h"

Game::Game()
{
    makeBoard();
    // row = 11;
    // col = 11;
    shipAmount = 0;
    player1 = nullptr;
    player2 = nullptr;
}

void Game::makeBoard()
{
    board = new int *[row];
    for (int i = 0; i < row; i++)
    {
        board[i] = new int[col];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            board[i][j] = 0;
        }
    }
    labels();
}
void Game::labels(){
    
    int val = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            board[0][1] = 'A';
            board[0][2] = 'B';
            board[0][3] = 'C';
            board[0][4] = 'D';
            board[0][5] = 'E';
            board[0][6] = 'F';
            board[0][7] = 'G';
            board[0][8] = 'H';
            board[0][9] = 'I';
            board[0][10] = 'J';
            board[i][0] = val;
            
        }
        val++;
    }
    board[0][0] = '-';
}

void Game::printBoard()
{
    for(int i=0; i<1; i++){
        for(int j=0; j<row; j++){
            std::cout << char(board[i][j]) << " ";
        }
    }
    std::cout <<'\n';
    for (int i = 1; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout <<'\n';
    }
}

void Game::playGame()
{
    std::cout << "Welcome to Battleship!" << std::endl;
    std::cout << "----------------------" << std::endl;
    do {
        std::cout << "Ship amount: ";
        std::cin >> shipAmount;
        if (shipAmount < 1 || shipAmount > 5)
        {
            std::cout << "Ship amount must be between 1-5." << std::endl;
        }
    } while(shipAmount < 1 || shipAmount > 5);
    Player* player1 = new Player(shipAmount);
    Player* player2 = new Player(shipAmount);
    obtainShips();


}

void Game::obtainShips()
{
    printBoard();
}
