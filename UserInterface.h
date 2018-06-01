#include "ConnectFour.h"
#include "TExaS.h"
#include "Nokia5110.h"


//************************display functions**********************

//nokia init
void StuffInit (void);


void WelcomeScene (void);

//Selects either single or multi. mode
// 1 = single, 2 = multi
int SelectModeScene (void);

//Selects either Master or Slave
// 1 = Master, 2 = Salve
int MSScene (void);

//select seed
//Selects either player1 = X or player2 = O
char SelectSeedScene(void);


//returns 1 if the user choosed to be the master, 0 otherwise
//int isMaster();

//Draws an empty ROWS*COLS grid
void drawEmptyGrid(void);

//Draws the seed[X, O] int column number col
void drawSeed(char seed, int col);

//Waiting Screen
void WaitingScene(void);

//Prints a screen with the given game state
void StateScene(GameState gameState);

//"You are player 1"
void displaySlaveSeed (int turn) ;

// time delay in 0.1 seconds
void Delay100ms(unsigned long count); 
