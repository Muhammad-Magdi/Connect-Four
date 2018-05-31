#include "ConnectFour.h"
#include "Nokia5110.h"
void WelcomeScene (void);

//Selects either single or multi. mode
// 1 = single, 2 = multi
int SelectModeScene (void);


//select seed
//Selects either player1 = X or player2 = O
char SelectSeedScene();


//returns 1 if the user choosed to be the master, 0 otherwise
//int isMaster();

//Draws an empty ROWS*COLS grid
void drawEmptyGrid();

//Draws the seed[X, O] int column number col
void drawSeed(char seed, int col);

//Waiting Screen
void WaitingScene();

//Prints a screen with the given game state
void StateScene(GameState gameState);

//"You are player 1"
void displaySlaveSeed (int turn) ;
