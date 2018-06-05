#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#define ROWS 6
#define COLS 7

typedef enum GameState{
	P1WIN, P2WIN, TIE, RUNNING, WAITING
} GameState;

//Takes a 2D grid and returns current game state
GameState checkGameState(void);

//Takes a 2D grid and returns the best position -column number- to play in
int bestPosition(char seed);

//Adds a seed into the game grid and increments the height array
void addSeed(char seed, int col);

//Initializes the board variables
void initializeBoard(void);

//returns the height of a given column
int heightOf(int);

void removeSeed(int);

#endif
