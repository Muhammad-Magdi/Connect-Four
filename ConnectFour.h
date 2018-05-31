#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#define ROWS 6
#define COLS 7

typedef enum GameState{
	P1Win, P2Win, Tie, Running, Waiting
} GameState;

//Takes a 2D grid and returns current game state
GameState checkGameState(char grid[ROWS][COLS]);

//Takes a 2D grid and returns the best position -column number- to play in
int bestPosition(char grid[ROWS][COLS]);

#endif
