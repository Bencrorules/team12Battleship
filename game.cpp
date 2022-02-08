#include <iostream>
#include "game.h"

Game::Game()
{
    makeBoard();
    row = 10;
    col = 10;
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
}

void Game::printBoard()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
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
