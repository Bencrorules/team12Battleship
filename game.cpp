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
    char tempxLetter;
    int tempyNumber;
    Ship* tempShip;
    printBoard();
    std::cout << std::endl;
    do
    {
        std::cout << "Player 1 - enter X coordinate for 1x1 ship (A-J): ";
        std::cin >> tempxLetter;
        if ((int)tempxLetter < 65 || (int)tempxLetter > 74)
        {
            std::cout << "Must enter letter between A and J." << std::endl;
        }
    } while((int)tempxLetter < 65 || (int)tempxLetter > 74);
    do
    {
        std::cout << "Player 1 - enter Y coordinate for 1x1 ship (1-10): ";
        std::cin >> tempyNumber;
        if (tempyNumber < 1 || tempyNumber > 10)
        {
            std::cout << "Must enter number between 1 and 10." << std::endl;
        }
    } while(tempyNumber < 1 || tempyNumber > 10);
    tempShip = new Ship(1);
    tempShip->setXCoord(0, tempxLetter);
    tempShip->setYCoord(0, tempyNumber);
    player1->addShip(0, tempShip);
    for (int i = 2; i <= shipAmount; i++)
    {
        tempShip = new Ship(i);
        for (int j = 0; j < i; j++)
        {
            /* Asking for X Coordinate */
            bool isValidXCoord = false;
            do // need to block entering coordinate that is not valid
            {
                std::cout << "Player 1 - enter X coordinate " << (j+1) << " for 1x" << i << " ship (A-J): ";
                std::cin >> tempxLetter;
                if (j > 0) // when the starting point was created
                {
                    if (abs((int)tempxLetter - (int)tempShip->getXCoord(j-1)) > 1) // if the coord is not next to previous
                    {
                        std::cout << "Must enter letter next to your previous coordinate." << std::endl;
                    }
                    else
                    {
                        isValidXCoord = true;
                    }
                }
                else
                {
                    isValidXCoord = true;
                }
                if ((int)tempxLetter < 65 || (int)tempxLetter > 74)
                {
                    std::cout << "Must enter letter between A and J." << std::endl;
                }
            } while((int)tempxLetter < 65 || (int)tempxLetter > 74 || !isValidXCoord);

            /* Asking for Y Coordinate */
            bool isValidYCoord = false;
            do
            {
                std::cout << "Player 1 - enter Y coordinate " << (j+1) << " for 1x" << i << " ship (1-10): ";
                std::cin >> tempyNumber;
                if (j > 0) // when the starting point was created
                {
                    if (abs(tempyNumber - tempShip->getYCoord(j-1)) > 1) // if the coord is not next to previous
                    {
                        std::cout << "Must enter letter next to your previous coordinate." << std::endl;
                    }
                    else
                    {
                        isValidYCoord = true;
                    }
                }
                else
                {
                    isValidYCoord = true;
                }
                if (tempyNumber < 1 || tempyNumber > 10)
                {
                    std::cout << "Must enter number between 1 and 10." << std::endl;
                }
            } while(tempyNumber < 1 || tempyNumber > 10 || !isValidYCoord);


            tempShip->setXCoord(j, tempxLetter);
            tempShip->setYCoord(j, tempyNumber);
        }

        player1->addShip(i-1, tempShip);

    }
    std::cout << std::endl;

    /* PLAYER 2 STARTS HERE */
    do
    {
        std::cout << "Player 2 - enter X coordinate for 1x1 ship (A-J): ";
        std::cin >> tempxLetter;
        if ((int)tempxLetter < 65 || (int)tempxLetter > 74)
        {
            std::cout << "Must enter letter between A and J." << std::endl;
        }
    } while((int)tempxLetter < 65 || (int)tempxLetter > 74);
    do
    {
        std::cout << "Player 2 - enter Y coordinate for 1x1 ship (1-10): ";
        std::cin >> tempyNumber;
        if (tempyNumber < 1 || tempyNumber > 10)
        {
            std::cout << "Must enter number between 1 and 10." << std::endl;
        }
    } while(tempyNumber < 1 || tempyNumber > 10);
    tempShip = new Ship(1);
    tempShip->setXCoord(0, tempxLetter);
    tempShip->setYCoord(0, tempyNumber);
    player2->addShip(0, tempShip);
    for (int i = 2; i <= shipAmount; i++)
    {
        tempShip = new Ship(i);
        for (int j = 0; j < i; j++)
        {
            /* Asking for X Coordinate */
            bool isValidXCoord = false;
            do // need to block entering coordinate that is not valid
            {
                std::cout << "Player 2 - enter X coordinate " << (j+1) << " for 1x" << i << " ship (A-J): ";
                std::cin >> tempxLetter;
                if (j > 0) // when the starting point was created
                {
                    if (abs((int)tempxLetter - (int)tempShip->getXCoord(j-1)) > 1) // if the coord is not next to previous
                    {
                        std::cout << "Must enter letter next to your previous coordinate." << std::endl;
                    }
                    else
                    {
                        isValidXCoord = true;
                    }
                }
                else
                {
                    isValidXCoord = true;
                }
                if ((int)tempxLetter < 65 || (int)tempxLetter > 74)
                {
                    std::cout << "Must enter letter between A and J." << std::endl;
                }
            } while((int)tempxLetter < 65 || (int)tempxLetter > 74 || !isValidXCoord);

            
            /* Asking for Y Coordinate */
            bool isValidYCoord = false;
            do
            {
                std::cout << "Player 1 - enter Y coordinate " << (j+1) << " for 1x" << i << " ship (1-10): ";
                std::cin >> tempyNumber;
                if (j > 0) // when the starting point was created
                {
                    if (abs(tempyNumber - tempShip->getYCoord(j-1)) > 1) // if the coord is not next to previous
                    {
                        std::cout << "Must enter letter next to your previous coordinate." << std::endl;
                    }
                    else
                    {
                        isValidYCoord = true;
                    }
                }
                else
                {
                    isValidYCoord = true;
                }
                if (tempyNumber < 1 || tempyNumber > 10)
                {
                    std::cout << "Must enter number between 1 and 10." << std::endl;
                }
            } while(tempyNumber < 1 || tempyNumber > 10 || !isValidYCoord);
            tempShip->setXCoord(j, tempxLetter);
            tempShip->setYCoord(j, tempyNumber);
        }
        player2->addShip(i-1, tempShip);
    }

}
