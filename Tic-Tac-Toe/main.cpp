//Tic Tac Toe
#include<bits/stdc++.h>
using namespace std;
#define COMPUTER 1
#define HUMAN 2
#define SIDE 3 // Declaration to intialise the board size later
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

// Function to display the filled board
void showBoard(char board[][SIDE])
{
    printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

// Function to display the default board to the player
void showInstructions()
{
    printf("\nChoose a cell numbered from 1 to 9 as below and play\n\n");
    printf("\t\t\t 1 | 2 | 3 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 4 | 5 | 6 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 7 | 8 | 9 \n\n");
}

// Function to initialise the board with '*' which indicates the empty positions to be filled
void initialise(char board[][SIDE])
{
    for (int i=0; i<SIDE; i++)
    {
        for (int j=0; j<SIDE; j++)
            board[i][j] = '*';
    }
}

// Function to display the winner of the game.
// Here, whoseTurn variable denotes the winner
void declareWinner(int whoseTurn)
{
    if (whoseTurn == COMPUTER)
        printf("COMPUTER has won\n");
    else
        printf("HUMAN has won\n");
}

// Function to find out whether all the 3 locations in any row contains the same symbol to find out the winner
bool rowCrossed(char board[][SIDE])
{
    for (int i=0; i<SIDE; i++)
    {
        // To find out whether the row has crossed, we must also ensure that no location in the same row contains '*'
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != '*')
            return (true);
    }
    return(false);
}

// Function to find out whether all the 3 locations in any column contains the same symbol to find out the winner
bool columnCrossed(char board[][SIDE])
{
    for (int i=0; i<SIDE; i++)
    {
        // To find out whether the column has been crossed, we must also ensure that no location in the same column contains '*'
        if (board[0][i] == board[1][i] &&
        board[1][i] == board[2][i] &&
        board[0][i] != '*')
            return (true);
    }
    return(false);
}

// Function to find out whether all the 3 locations along any diagonal contains the same symbol to find out the winner
bool diagonalCrossed(char board[][SIDE])
{
    // To find out whether the principal diagonal has been crossed, we must also ensure that no location in the same diagonal contains '*'
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != '*')
        return(true);
    
    // To find out whether the cross-diagonal has been crossed, we must also ensure that no location in the same diagonal contains '*'
    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        board[0][2] != '*')
        return(true);
    return(false);
}

// Function to find out whether the game has ended or not
// The game is said to have ended if either the row, column, diagonal or principal diagonal has been crossed out
bool gameOver(char board[][SIDE])
{
    return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board) );
}

// Function to demonstrate the Minimax algorithm to return the best score
// Minimax algorithm is a backtracking algorithm that finds an optimal and the best solution
// If score = +10, human player has won
// If score = -10, computer has won
// If score = 0, its a tie
// This function is applicable only for computer's move
int minimax(char board[][SIDE], int depth, bool isAI)
{
    int score = 0;
    int bestScore = 0;
    if (gameOver(board) == true) // This denotes that game is over and a winner is declared
    {
        if (isAI == true) // This condition indicates that computer has won
            return -10;
        if (isAI == false) // This condition indicates that human player has won
            return +10;
    }
    else
    {
        // depth variable ensures that the location of board is within bounds and the board isn't completely filled
        if(depth < 9)
        {
            if(isAI == true) // This indicates computer's turn
            {
                bestScore = -999; // initially set to -infinity
                for(int i=0; i<SIDE; i++)
                {
                    for(int j=0; j<SIDE; j++)
                    {
                        if (board[i][j] == '*') // location is blank
                        {
                            board[i][j] = COMPUTERMOVE; // filling 1st discovered blank location with computer's move
                            score = minimax(board, depth + 1, false); // updating the score to decide the winner
                            board[i][j] = '*'; // filling the location with '*' which required during backtracking and when there exists more optimal location that this
                            if(score > bestScore)
                            {
                                bestScore = score; // updating an optimal and best score
                            }
                        }
                    }
                }
                return bestScore;
            }
            else
            {
                // In case of human player's turn
                bestScore = 999;
                for (int i = 0; i < SIDE; i++)
                    {
                        for (int j = 0; j < SIDE; j++)
                        {
                            if (board[i][j] == '*')
                            {
                                board[i][j] = HUMANMOVE;
                                score = minimax(board, depth + 1, true);
                                board[i][j] = '*';
                                if (score < bestScore)
                                {
                                    bestScore = score;
                                }
                            }
                        }
                    }
                    return bestScore;
                }
            }
            else
            {
                return 0;
            }
        }
    }

// Function to return the best location for computer's move
int bestMove(char board[][SIDE], int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = COMPUTERMOVE;
                score = minimax(board, moveIndex+1, false);
                board[i][j] = '*';
                if(score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x*3+y; // This gives the location of best move
}

// A function to play Tic-Tac-Toe
void playTicTacToe(int whoseTurn)
{
    //Intialise the board size to be 3X3
    char board[SIDE][SIDE];
    int moveIndex = 0, x = 0, y = 0; // moveIndex is initialised as the locations of the board are filled
    initialise(board);
    showInstructions();
    while (gameOver(board) == false && moveIndex != SIDE*SIDE) // When the game is not yet over
    {
        int n;
        if (whoseTurn == COMPUTER)
        {
            n = bestMove(board, moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = COMPUTERMOVE;
            printf("COMPUTER has put a %c in cell %d\n\n", COMPUTERMOVE, n+1);
            showBoard(board);
            moveIndex ++;
            whoseTurn = HUMAN;
        }
        else if (whoseTurn == HUMAN)
        {
            printf("You can insert in the following positions : ");
            for(int i=0; i<SIDE; i++)
                for (int j = 0; j < SIDE; j++)
                    if (board[i][j] == '*')
                        printf("%d ", (i * 3 + j) + 1);
                        printf("\n\nEnter the position = ");
                        scanf("%d",&n);
                        n--; // n gets decremented each time a location in the board is filled
                        x = n / SIDE;
                        y = n % SIDE;
                        if(board[x][y] == '*' && n<9 && n>=0)// To ensure that the location is within the bounds and is empty
                        {
                            board[x][y] = HUMANMOVE;
                            printf ("\nHUMAN has put a %c in cell %d\n\n", HUMANMOVE, n+1);
                            showBoard(board);
                            moveIndex ++;
                            whoseTurn = COMPUTER;// To initialise the next turn to computer
                        }
                        else if(board[x][y] != '*' && n<9 && n>=0)
                        {
                            printf("\nPosition is occupied, select any one place from the available places\n\n");
                        }
                        else if(n<0 || n>8)// Location out-of-bounds
                        {
                            printf("Invalid position\n");
                        }
        }
    }
    if (gameOver(board) == false && moveIndex == SIDE * SIDE)
        printf("It's a draw\n");
    else
    {
        if (whoseTurn == COMPUTER)
            whoseTurn = HUMAN;
        else if (whoseTurn == HUMAN)
            whoseTurn = COMPUTER;
        declareWinner(whoseTurn); // whoseTurn variable declares the winner
        }
}

int main()
{
    printf("\n-------------------------------------------------------------------\n\n");
    printf("\t\t\t Tic-Tac-Toe\n");
    printf("\n-------------------------------------------------------------------\n\n");
    char cont='y';
    do {
        char choice;
        printf("Do you want to start first?(y/n) : ");
        scanf(" %c", &choice);
        if(choice=='n')
            playTicTacToe(COMPUTER);
        else if(choice=='y')
            playTicTacToe(HUMAN);
        else
            printf("Invalid choice\n");
            printf("\nDo you want to quit(y/n) : ");
            scanf(" %c", &cont);
        } 
        while(cont=='n');
    return (0);
}