#include <iostream>
//#include <charconv>
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
void Game::labels()
{

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
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < row; j++)
        {
            std::cout << char(board[i][j]) << " ";
        }
    }
    std::cout << '\n';
    for (int i = 1; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << '\n';
    }
}

void Game::playGame()
{
    std::cout << "Welcome to Battleship!" << std::endl;
    std::cout << "----------------------" << std::endl;
    do
    {
        std::cout << "Ship amount: ";
        std::cin >> shipAmount;
        if (shipAmount < 1 || shipAmount > 5)
        {
            std::cout << "Ship amount must be between 1-5." << std::endl;
        }
    } while (shipAmount < 1 || shipAmount > 5);
    player1 = new Player(shipAmount);
    player2 = new Player(shipAmount);

    obtainShips();
    playerGuess();
}

void Game::obtainShips()
{
    char tempxLetter;
    int tempyNumber;
    printBoard();
    std::cout << std::endl;

    /* PLAYER 1 STARTS HERE */
    do
    {
        std::cout << "Player 1 - enter X coordinate for 1x1 ship (A-J): ";
        std::cin >> tempxLetter;
        if ((int)tempxLetter < 65 || (int)tempxLetter > 74)
        {
            std::cout << "Must enter letter between A and J." << std::endl;
        }
    } while ((int)tempxLetter < 65 || (int)tempxLetter > 74);
    do
    {
        std::cout << "Player 1 - enter Y coordinate for 1x1 ship (1-10): ";
        std::cin >> tempyNumber;
        if (tempyNumber < 1 || tempyNumber > 10)
        {
            std::cout << "Must enter number between 1 and 10." << std::endl;
        }
    } while (tempyNumber < 1 || tempyNumber > 10);

    player1->addShip(0, 0, tempxLetter, tempyNumber, 1); // temp line - Lee
    player1->getShipInfo(0, 0);                          // temp line - Lee :: it seems like it is updating the information above function.
    /*
    tempShip = new Ship(1);
    tempShip->setXCoord(0, tempxLetter);
    tempShip->setYCoord(0, tempyNumber);
    player1->addShip(0, tempShip);
    */

    /* Player 1 - Ship creation when shipAmount is more than 1 */
    for (int i = 2; i <= shipAmount; i++)
    {
        for (int j = 0; j < i; j++)
        {
            int prevX, prevY;
            /* Asking for X Coordinate */
            bool isValidCoord = false;

            /* Check if coordinates are valid */
            do
            {
                do // need to block entering coordinate that is not valid
                {
                    std::cout << "Player 1 - enter X coordinate " << (j + 1) << " for 1x" << i << " ship (A-J): ";
                    std::cin >> tempxLetter;
                    if ((int)tempxLetter < 65 || (int)tempxLetter > 74)
                    {
                        std::cout << "Must enter letter between A and J." << std::endl;
                    }
                } while ((int)tempxLetter < 65 || (int)tempxLetter > 74);

                /* Asking for Y Coordinate */
                do
                {
                    std::cout << "Player 1 - enter Y coordinate " << (j + 1) << " for 1x" << i << " ship (1-10): ";
                    std::cin >> tempyNumber;
                    if (tempyNumber < 1 || tempyNumber > 10)
                    {
                        std::cout << "Must enter number between 1 and 10." << std::endl;
                    }
                } while (tempyNumber < 1 || tempyNumber > 10);

                /*
                tempShip->setXCoord(j, tempxLetter);
                tempShip->setYCoord(j, tempyNumber);
                */

                // *need to add condition check if coord overlaps with prev ship coords*
                if (j == 0) // when it is first time entering coordinate with multiple coord ship
                {
                    isValidCoord = true;
                }
                else
                {
                    if (
                        // if coordinates are not next to previous coordinates
                        ((abs((int)tempxLetter - prevX > 1)) || (abs(tempyNumber - prevY) > 1))
                        // if coordinates overlap with previous coord
                        || ((abs((int)tempxLetter - prevX) == 0) && (abs(tempyNumber - prevY) == 0))

                    )
                    {
                        std::cout << "Must enter a new coordinate that is next to your previous coordinate." << std::endl;
                        std::cout << "Previous Coordinate : " << prevX << ", " << prevY << std::endl;
                    }
                    else
                    {
                        isValidCoord = true;
                    }
                }
            } while (!isValidCoord);
            prevX = (int)tempxLetter;
            prevY = tempyNumber;
            player1->addShip(i - 1, j, tempxLetter, tempyNumber, i); // temp line - Lee
            player1->getShipInfo(i - 1, j);                          // temp line - Lee :: it seems like it is updating the information above function.
        }

        // player1->addShip(i-1, tempShip);
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
    } while ((int)tempxLetter < 65 || (int)tempxLetter > 74);
    do
    {
        std::cout << "Player 2 - enter Y coordinate for 1x1 ship (1-10): ";
        std::cin >> tempyNumber;
        if (tempyNumber < 1 || tempyNumber > 10)
        {
            std::cout << "Must enter number between 1 and 10." << std::endl;
        }
    } while (tempyNumber < 1 || tempyNumber > 10);

    player2->addShip(0, 0, tempxLetter, tempyNumber, 1); // temp line - Lee
    player2->getShipInfo(0, 0);                          // temp line - Lee :: it seems like it is updating the information above function.
    /*
    tempShip = new Ship(1);
    tempShip->setXCoord(0, tempxLetter);
    tempShip->setYCoord(0, tempyNumber);
    player2->addShip(0, tempShip);
    */

    /* PLAYER 2 When ship amount is more than one */
    for (int i = 2; i <= shipAmount; i++)
    {
        for (int j = 0; j < i; j++)
        {
            int prevX, prevY;

            /* Asking for X Coordinate */
            bool isValidCoord = false;
            do
            {

                do // need to block entering coordinate that is not valid
                {
                    std::cout << "Player 2 - enter X coordinate " << (j + 1) << " for 1x" << i << " ship (A-J): ";
                    std::cin >> tempxLetter;
                    if ((int)tempxLetter < 65 || (int)tempxLetter > 74)
                    {
                        std::cout << "Must enter letter between A and J." << std::endl;
                    }
                } while ((int)tempxLetter < 65 || (int)tempxLetter > 74);

                /* Asking for Y Coordinate */
                do
                {
                    std::cout << "Player 1 - enter Y coordinate " << (j + 1) << " for 1x" << i << " ship (1-10): ";
                    std::cin >> tempyNumber;
                    if (tempyNumber < 1 || tempyNumber > 10)
                    {
                        std::cout << "Must enter number between 1 and 10." << std::endl;
                    }
                } while (tempyNumber < 1 || tempyNumber > 10);
                /*
                tempShip->setXCoord(j, tempxLetter);
                tempShip->setYCoord(j, tempyNumber);
                */

                // *need to add condition check if coord overlaps with prev ship coords*
                if (j == 0) // when it is first time entering coordinate with multiple coord ship
                {
                    isValidCoord = true;
                }
                else
                {
                    if (
                        // if coordinates are not next to previous coordinates
                        ((abs((int)tempxLetter - prevX > 1)) || (abs(tempyNumber - prevY) > 1))
                        // if coordinates overlap with previous coord
                        || ((abs((int)tempxLetter - prevX) == 0) && (abs(tempyNumber - prevY) == 0))

                    )
                    {
                        std::cout << "Must enter a new coordinate that is next to your previous coordinate." << std::endl;
                        std::cout << "Previous Coordinate : " << prevX << ", " << prevY << std::endl;
                    }
                    else
                    {
                        isValidCoord = true;
                    }
                }
            } while (!isValidCoord);
            prevX = (int)tempxLetter;
            prevY = tempyNumber;
            player2->addShip(i - 1, j, tempxLetter, tempyNumber, i); // temp line - Lee
            player2->getShipInfo(i - 1, j);                          // temp line - Lee :: it seems like it is updating the information above function.
        }

        // player2->addShip(i-1, tempShip);
    }
}

void Game::playerGuess()
{
    char xGuess;
    int yGuess;
    do
    {
        std::cout << "Player 1 - enter X coordinate (A-J): ";
        std::cin >> xGuess;
        if ((int)xGuess < 65 || (int)xGuess > 74)
        {
            std::cout << "Must enter letter between A and J\n";
        }
    } while ((int)xGuess < 65 || (int)xGuess > 74);
    // std::cout << xGuess << '\n';
    do
    {
        std::cout << "Player 1 - enter Y coordinate (1-10): ";
        std::cin >> yGuess;
        if (yGuess < 1 || yGuess > 10)
        {
            std::cout << "Must enter number between 1 and 10\n";
        }
    } while (yGuess < 1 || yGuess > 10);
    // std::cout << yGuess << '\n';
}
