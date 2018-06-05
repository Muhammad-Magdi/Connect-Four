#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "ConnectFour.h"

//************************display functions**********************

//nokia init
void NokiaInit (void);

void welcomeScene (void);

//Selects either single or multi. mode
// 1 = single, 2 = multi
int selectModeScene (void);

//Selects either Master or Slave
// 1 = Master, 2 = Salve
int MSScene (void);

//select seed
//Selects either player1 = X or player2 = O
char selectSeedScene(void);


//returns 1 if the user choosed to be the master, 0 otherwise
//int isMaster();

//Draws an empty ROWS*COLS grid
void drawEmptyGrid(void);

//Draws the seed[X, O] int column number col
void drawSeed(char seed, int col , int row);

//Waiting Screen
void waitingScene(void);

//Waiting Screen
void connectingScene(void);

//Prints a screen with the given game state
void stateScene(GameState gameState, char seed);

//"You are player 1"
void displaySlaveSeed (unsigned short turn) ;

// time delay in 0.1 seconds
void Delay100ms(unsigned long count); 

void drawInvertedSeed(char seed, int col ,int row);

void winGrid (void);

void fullGrid (void);

void winScene (void);

void genPoint(void);

#endif
