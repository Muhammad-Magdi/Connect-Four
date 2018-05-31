#include "ConnectFour.h"

//Selects either single or multi. mode
// 1 = single, 2 = multi
int selectMode();

//returns 1 if the user choosed to be the master, 0 otherwise
int isMaster();

//Selects either player1 = X or player2 = O
char selectSeed();

//Draws an empty ROWS*COLS grid
void drawEmptyGrid();

//Draws the seed[X, O] int column number col
void drawSeed(char seed, int col);

//Waiting Screen
void waiting();

//Prints a screen with the given game state
void drawState(GameState gameState);
