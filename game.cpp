#include <iostream>
#include <limits>
#include "game.h"

Game::Game() // game constructor
{
    makeBoard(); // calls maeBoard function
    // row = 11;
    // col = 11;
    shipAmount = 0;    // sets shipAmount to 0 for the start of a board
    player1 = nullptr; // sets the player1 pointer to nullptr
    player2 = nullptr; // sets the player2 pointer to nullptr
}

Game::~Game()
{ // game destructor
    for (int i = 0; i < row; i++)
    {                      // runs for each row in the board
        delete[] board[i]; // deletes the row at int i
    }
    delete[] board; // deletes the empty board
    delete player1; // deletes the player1 pointer
    delete player2; // deletes the player2 pointer
}

void Game::makeBoard() // game class function 'makeBoard' creates an int 2D array initialized to 0
{
    board = new int *[row];       // sets board as a new array of ints
    for (int i = 0; i < row; i++) // for each row of the board...
    {
        board[i] = new int[col]; // set the row of board at int i to have a columb effectively creating a 2d array
    }

    for (int i = 0; i < row; i++) // for each row of the board...
    {
        for (int j = 0; j < col; j++) // for each columb of the board...
        {
            board[i][j] = 0; // initialze value to 0
        }
    }
    labels(); // call the labels function
}

void Game::labels() // game class function 'labels' sets the values on the edges of the board to their coordinate representations
{
    board[0][0] = '-'; // this line and the following 10 set the first row of the board to visually represent coordinates
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

    int val = 1;                  // initializes an int 'val' to 0. only within the scope of labels function
    for (int i = 1; i < row; i++) // for each row of the board...
    {
        board[i][0] = val; // sets the first columb of the board to values 1-10
        val++;             // increases val by 1 each iteration of the for loop
    }
}

void Game::printBoard() // game class function 'printBoard' prints the board to the command line
{
    for (int i = 0; i < row; i++) // for each row of the board...
    {
        for (int j = 0; j < col; j++) // for each columb of the board...
        {
            if (j == 0 && 0 < i && i < 10) // if the coordinate is on the first columb and on row 1 through 9...
            {
                std::cout << board[i][j] << "  "; // print the board value with correct visual spacing
            }
            else
            {
                if ((int)board[i][j] > 10)
                {
                    std::cout << (char)board[i][j] << " ";
                    if (i == 0 && j == 0) // if '-'
                    {
                        std::cout << " ";
                    }
                }
                else
                {
                    std::cout << board[i][j] << " ";
                }
            }
        }
        std::cout << '\n'; // print new line
    }
}

void Game::playGame() // game class function 'playGame' controls much of the game logic
{
    std::cout << "Welcome to Battleship!" << std::endl; // prints out welcome message
    std::cout << "----------------------" << std::endl; // prints out visual break
    do                                                  // loop at least once
    {
        std::cout << "Ship amount: "; // ask for ship amount
        std::cin >> shipAmount;       // store player entry to shipAmount variable

        while (std::cin.fail()) // while input failed
        {
            std::cin.clear();                                                   // clear the cache
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore bad values

            std::cout << "Ship amount (1-5): "; // ask again for the ship amount
            std::cin >> shipAmount;       // store player entry to shipAmount
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore bad values
        if (shipAmount < 1 || shipAmount > 5)                               // if the shipAmount isn't 1-5...
        {
            std::cout << "Ship amount must be between 1-5." << std::endl; // tell player ship amount must be between 1-5
        }
    } while (shipAmount < 1 || shipAmount > 5); // loop if the shipAmount isn't between 1 and 5
    player1 = new Player(shipAmount);           // declares player1 as a new Player with the shipAmount
    player2 = new Player(shipAmount);           // declares player2 as a new Player with the shipAmount

    obtainShips(); // calls the obtainShips function
    playerGuess(); // calls the playerGuess function
}

void Game::obtainShips() // game class function 'obtainShips'
{
    char tempxLetter;       // declares char tempxLetter
    int tempyNumber;        // declares int tempyNumber
    printBoard();           // prints the board
    std::cout << std::endl; // creates a new line

    /* PLAYER 1 STARTS HERE */
    do // loop at least once
    {
        std::cout << "Player 1 - enter X coordinate for 1x1 ship (A-J): "; // ask player 1 for the x coordinate of their 1x1 ship
        std::cin >> tempxLetter;                                           // store player input to tempxLetter

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // if double input such as AA, will only take A as input
        //  std::cout << (char)tempxLetter << '\n';
        if ((int)tempxLetter < 65 || (int)tempxLetter > 74) // if unicode for the player input isn't between 65 and 74 (A-J)
        {
            std::cout << "Must enter letter between A and J." << std::endl; // inform player of the error
        }
    } while ((int)tempxLetter < 65 || (int)tempxLetter > 74); // then loop again
    do                                                        // loop at least once
    {
        std::cout << "Player 1 - enter Y coordinate for 1x1 ship (1-10): "; // ask player for the y coordinate for their 1x1 ship
        std::cin >> tempyNumber;                                            // store player input

        while (std::cin.fail()) // while the input is invalid...
        {
            std::cin.clear();                                                   // clear cache
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the value

            std::cout << "Player 1 - enter Y coordinate for 1x1 ship (1-10): "; // ask player again for the value
            std::cin >> tempyNumber;                                            // store player input
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the value

        if (tempyNumber < 1 || tempyNumber > 10) // if the player input isn't between 1 and 10...
        {
            std::cout << "Must enter number between 1 and 10." << std::endl; // inform player of error
        }
    } while (tempyNumber < 1 || tempyNumber > 10); // loop if input isn't between 1 and 10

    player1->addShip(0, 0, tempxLetter, tempyNumber, 1); // temp line - Lee
    player1->getShipInfo(0, 0);                          // temp line - Lee :: it seems like it is updating the information above function.

    /* Player 1 - Ship creation when shipAmount is more than 1 */
    for (int i = 2; i <= shipAmount; i++) // for the second ship and each one after...
    {
        for (int j = 0; j < i; j++) // for each coordinate of the new ship...
        {
            int prevX, prevY; // declare ints prevX and prevY
            /* Asking for X Coordinate */
            bool isValidCoord = false; // declare bool isValidCoord initialized to false

            /* Check if coordinates are valid */
            do
            {
                do // need to block entering coordinate that is not valid
                {
                    std::cout << "Player 1 - enter X coordinate " << (j + 1) << " for 1x" << i << " ship (A-J): ";
                    std::cin >> tempxLetter;

                    // Input Check (1) :: if input is not single char
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // if double input such as AA, will only take A as input
                    // Input Check (2) :: if input is not in range
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

                    while (std::cin.fail())
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        std::cout << "Player 1 - enter Y coordinate " << (j + 1) << " for 1x" << i << " ship (1-10): ";
                        std::cin >> tempyNumber;
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (tempyNumber < 1 || tempyNumber > 10)
                    {
                        std::cout << "Must enter number between 1 and 10." << std::endl;
                    }
                } while (tempyNumber < 1 || tempyNumber > 10);

                // *need to add condition check if coord overlaps with prev ship coords*
                if (j == 0) // when it is first time entering coordinate with multiple coord ship
                {
                    if (isOverlapCoord(player1,tempxLetter, tempyNumber))
                    {
                        isValidCoord = false;
                        std::cout << "[SYSTEM] - Coordinate overlapes with existing coordinate!" << std::endl;
                        std::cout << "[SYSTEM] - Overlapping Coordinate : " << tempxLetter << ", " << tempyNumber << std::endl;
                    }
                    else
                    {
                        isValidCoord = true;
                    }
                }
                else
                {
                    if ( // Input Check (4) :: Coord is next to previous coordinate (e.g. should not be A1, A3)
                        // if coordinates are not next to previous coordinates
                        ((abs((int)tempxLetter - prevX > 1)) || (abs(tempyNumber - prevY) > 1))
                        // if coordinates overlap with previous coord
                        || ((abs((int)tempxLetter - prevX) == 0) && (abs(tempyNumber - prevY) == 0))

                    )
                    {
                        std::cout << "[SYSTEM] - Must enter a new coordinate that is next to your previous coordinate." << std::endl;
                        std::cout << "[SYSTEM] - Previous Coordinate : " << prevX << ", " << prevY << std::endl;
                    }
                    else
                    {
                        if (!isOverlapCoord(player1,tempxLetter, tempyNumber))
                        {
                            isValidCoord = true;
                        }
                        else
                        {
                            std::cout << "[SYSTEM] - Coordinate overlapes with existing coordinate!" << std::endl;
                            std::cout << "[SYSTEM] - Overlapping Coordinate : " << tempxLetter << ", " << tempyNumber << std::endl;
                        }
                    }
                }
            } while (!isValidCoord);
            prevX = (int)tempxLetter;
            prevY = tempyNumber;
            player1->addShip(i - 1, j, tempxLetter, tempyNumber, i); // temp line - Lee
            player1->getShipInfo(i - 1, j);                          // temp line - Lee :: it seems like it is updating the information above function.
        }
    }
    std::cout << std::endl;

    /* PLAYER 2 STARTS HERE */
    do
    {
        std::cout << "Player 2 - enter X coordinate for 1x1 ship (A-J): ";
        std::cin >> tempxLetter;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // if double input such as AA, will only take A as input
        if ((int)tempxLetter < 65 || (int)tempxLetter > 74)
        {
            std::cout << "Must enter letter between A and J." << std::endl;
        }
    } while ((int)tempxLetter < 65 || (int)tempxLetter > 74);
    do
    {
        std::cout << "Player 2 - enter Y coordinate for 1x1 ship (1-10): ";
        std::cin >> tempyNumber;

        while (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Player 2 - enter Y coordinate for 1x1 ship (1-10): ";
            std::cin >> tempyNumber;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (tempyNumber < 1 || tempyNumber > 10)
        {
            std::cout << "Must enter number between 1 and 10." << std::endl;
        }
    } while (tempyNumber < 1 || tempyNumber > 10);

    player2->addShip(0, 0, tempxLetter, tempyNumber, 1); // temp line - Lee
    player2->getShipInfo(0, 0);                          // temp line - Lee :: it seems like it is updating the information above function.

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
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // if double input such as AA, will only take A as input
                    if ((int)tempxLetter < 65 || (int)tempxLetter > 74)
                    {
                        std::cout << "Must enter letter between A and J." << std::endl;
                    }
                } while ((int)tempxLetter < 65 || (int)tempxLetter > 74);

                /* Asking for Y Coordinate */
                do
                {
                    std::cout << "Player 2 - enter Y coordinate " << (j + 1) << " for 1x" << i << " ship (1-10): ";
                    std::cin >> tempyNumber;

                    while (std::cin.fail())
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        std::cout << "Player 2 - enter Y coordinate " << (j + 1) << " for 1x " << i << " ship (1-10): ";
                        std::cin >> tempyNumber;
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (tempyNumber < 1 || tempyNumber > 10)
                    {
                        std::cout << "Must enter number between 1 and 10." << std::endl;
                    }

                } while (tempyNumber < 1 || tempyNumber > 10);

                // *need to add condition check if coord overlaps with prev ship coords*
                if (j == 0) // when it is first time entering coordinate with multiple coord ship
                {
                    if (isOverlapCoord(player2,tempxLetter, tempyNumber))
                    {
                        isValidCoord = false;
                        std::cout << "[SYSTEM] - Coordinate overlapes with existing coordinate!" << std::endl;
                        std::cout << "[SYSTEM] - Overlapping Coordinate : " << tempxLetter << ", " << tempyNumber << std::endl;
                    }
                    else
                    {
                        isValidCoord = true;
                    }
                }
                else
                {
                    if ( // Input Check (4) :: Coord is next to previous coordinate (e.g. should not be A1, A3)
                        // if coordinates are not next to previous coordinates
                        ((abs((int)tempxLetter - prevX > 1)) || (abs(tempyNumber - prevY) > 1))
                        // if coordinates overlap with previous coord
                        || ((abs((int)tempxLetter - prevX) == 0) && (abs(tempyNumber - prevY) == 0))

                    )
                    {
                        std::cout << "[SYSTEM] - Must enter a new coordinate that is next to your previous coordinate." << std::endl;
                        std::cout << "[SYSTEM] - Previous Coordinate : " << prevX << ", " << prevY << std::endl;
                    }
                    else
                    {
                        if (!isOverlapCoord(player2,tempxLetter, tempyNumber))
                        {
                            isValidCoord = true;
                        }
                        else
                        {
                            std::cout << "[SYSTEM] - Coordinate overlapes with existing coordinate!" << std::endl;
                            std::cout << "[SYSTEM] - Overlapping Coordinate : " << tempxLetter << ", " << tempyNumber << std::endl;
                        }
                    }
                }
            } while (!isValidCoord);
            prevX = (int)tempxLetter;
            prevY = tempyNumber;
            player2->addShip(i - 1, j, tempxLetter, tempyNumber, i); // temp line - Lee
            player2->getShipInfo(i - 1, j);                          // temp line - Lee :: it seems like it is updating the information above function.
        }
    }
}

bool Game::isOverlapCoord(Player* thisPlayer, char xLetter, int yNumber)
{
    // Input Check (3) :: if input overlaps with coordinates of existing ship
    for (int i = 0; i < shipAmount; i++) // for each ship
    {
        for (int j = 0; j < (i + 1); j++) // for each position of coordinates
            if (thisPlayer->getShip(i)->getXCoord(j) == xLetter && thisPlayer->getShip(i)->getYCoord(j) == yNumber)
            {
                return true;
            }
    }
    return false;
}

void Game::playerGuess()
{
    char xGuess;
    int yGuess;

    /* PLAYER 1 : Guessing Coordinates */
    while (!gameFinished)
    {
        do
        {
            std::cout << "[ATTACK] Player 1 - enter X coordinate (A-J): ";
            std::cin >> xGuess;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // if double input such as AA, will only take A as input
            if ((int)xGuess < 65 || (int)xGuess > 74)
            {
                std::cout << "Must enter letter between A and J\n";
            }
        } while ((int)xGuess < 65 || (int)xGuess > 74);
        // std::cout << xGuess << '\n';
        do
        {
            std::cout << "[ATTACK] Player 1 - enter Y coordinate (1-10): ";
            std::cin >> yGuess;

            while (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "[ATTACK] Player 1 - enter Y coordinate (1-10): ";
                std::cin >> yGuess;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (yGuess < 1 || yGuess > 10)
            {
                std::cout << "Must enter number between 1 and 10\n";
            }

        } while (yGuess < 1 || yGuess > 10);
        // std::cout << yGuess << '\n';

        /* Where we need to update new board */
        if (player2->shipAttacked(xGuess, yGuess)) // handle player
        {
            // 65 is A, to make A number 1 index, -64
            board[((int)xGuess) - 64][yGuess] = 'R'; // if it hits ship, update board coord to 'RED'
            if (player2->allShipDown())
            {
                finishGame(1);
            }
        }
        else
        {
            board[((int)xGuess) - 64][yGuess] = 'W'; // if it didn't hit anything, update board coord to 'WHITE'
        }
        // printBoardP1();

        if (!gameFinished)
        {
            /* PLAYER 2 : Guessing Coordinates */
            do
            {
                std::cout << "[ATTACK] Player 2 - enter X coordinate (A-J): ";
                std::cin >> xGuess;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // if double input such as AA, will only take A as input
                if ((int)xGuess < 65 || (int)xGuess > 74)
                {
                    std::cout << "Must enter letter between A and J\n";
                }
            } while ((int)xGuess < 65 || (int)xGuess > 74);
            // std::cout << xGuess << '\n';
            do
            {
                std::cout << "[ATTACK] Player 2 - enter Y coordinate (1-10): ";
                std::cin >> yGuess;

                while (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    std::cout << "[ATTACK] Player 2 - enter Y coordinate (1-10): ";
                    std::cin >> yGuess;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (yGuess < 1 || yGuess > 10)
                {
                    std::cout << "Must enter number between 1 and 10\n";
                }

            } while (yGuess < 1 || yGuess > 10);
            // std::cout << yGuess << '\n';

            /* Where we need to update new board */
            if (player1->shipAttacked(xGuess, yGuess)) // handle player
            {
                // 65 is A, to make A number 1 index, -64
                board[((int)xGuess) - 64][yGuess] = 'R'; // if it hits ship, update board coord to 'RED'
                if (player1->allShipDown())
                {
                    finishGame(2);
                }
            }
            else
            {
                board[((int)xGuess) - 64][yGuess] = 'W'; // if it didn't hit anything, update board coord to 'WHITE'
            }
            // printBoardP2();
        }
    }
}

void Game::finishGame(int winner)
{
    std::cout << "Player " << winner << " wins the game! \n";
    gameFinished = true;
}