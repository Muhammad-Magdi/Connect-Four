#include <stdio.h>
#include <stdlib.h>
#include "ConnectFour.h"
#include "string.h"


char gameGrid[ROWS][COLS];
int columnHeight[COLS];
GameState currentState;
char currentTurn;

char player1 = 'X', player2 = 'O';
int INF = 1e9;
int max(int a, int b){
  if(a >= b)
    return a;
  return b;
}

int min(int a, int b){
  if(a <= b)
    return a;
  return b;
}

int isMovesLeft(){
  int i;
	for(i=0; i<COLS; i++){
    if(columnHeight[i] < ROWS)
      return 1;
  }
  return 0;
}


// 100 = player1 Wins
// -100 = player2 wins
// 0 = RUNNING
int evaluate(){
	int i, j;
  for(i=0; i<ROWS; i++){
    for(j=0; j<COLS; j++){
      if(j<4 && gameGrid[i][j]==gameGrid[i][j+1] && gameGrid[i][j]==gameGrid[i][j+2] && gameGrid[i][j]==gameGrid[i][j+3]){
        if(gameGrid[i][j] == player1)
          return 100;
        else if(gameGrid[i][j] == player2)
          return -100;
      }
      if(i<3 && gameGrid[i][j]==gameGrid[i+1][j] && gameGrid[i][j]==gameGrid[i+2][j] && gameGrid[i][j]==gameGrid[i+3][j]){
        if(gameGrid[i][j] == player1)
          return 100;
        else if(gameGrid[i][j] == player2)
          return -100;
      }
      if(i<3 && j<4 && gameGrid[i][j]==gameGrid[i+1][j+1] && gameGrid[i][j]==gameGrid[i+2][j+2] && gameGrid[i][j]==gameGrid[i+3][j+3]){
        if(gameGrid[i][j] == player1)
          return 100;
        else if(gameGrid[i][j] == player2)
          return -100;
      }
      if(i>2 && j<4 && gameGrid[i][j]==gameGrid[i-1][j+1] && gameGrid[i][j]==gameGrid[i-2][j+2] && gameGrid[i][j]==gameGrid[i-3][j+3]){
        if(gameGrid[i][j] == player1)
          return 100;
        else if(gameGrid[i][j] == player2)
          return -100;
      }
    }
  }
  return 0;
}

int minimax(int depth, int isMax, int alpha, int beta){
  int score = evaluate(), i;
  if(depth == 6)
    return score;
  if(score == 100)
    return score;
  if(score == -100)
    return score;
  if(isMovesLeft() == 0)
    return 0;
  if(isMax == 1){
    int best = -INF;
    for(i=0; i<COLS; i++){
      if(columnHeight[i] < ROWS){
        gameGrid[columnHeight[i]++][i] = player1;
        best = max(best, minimax(depth+1, 2, alpha, beta));
        alpha = max(alpha, best);
        gameGrid[--columnHeight[i]][i] = 0;
      }
      if(beta <= alpha)
        break;
    }
    return best;
  }
  else{
    int best = INF;
    for(i=0; i<COLS; i++){
      if(columnHeight[i] < ROWS){
        gameGrid[columnHeight[i]++][i] = player2;
        best = min(best, minimax(depth+1, 1, alpha, beta));
        beta = min(beta, best);
        gameGrid[--columnHeight[i]][i] = 0;
      }
      if(beta <= alpha)
        break;
    }
    return best;
  }
}

int bestMoveP1(){
  int bestVal = -INF, ret = -1, i, moveVal;
  for(i=0; i<COLS; i++){
    if(columnHeight[i] < ROWS){
      addSeed(player1, i);
      moveVal = minimax(0, 2, -INF, INF);
      removeSeed(i);
      if(moveVal > bestVal){
        ret = i;
        bestVal = moveVal;
      }
    }
  }
  return ret;
}

int bestMoveP2(){
  int bestVal = INF, ret = -1, i, moveVal;
	
  for(i=0; i<COLS; i++){
    if(columnHeight[i] < ROWS){
      addSeed(player2, i);
      moveVal = minimax(0, 1, -INF, INF);
      removeSeed(i);
      if(moveVal < bestVal){
        ret = i;
        bestVal = moveVal;
      }
    }
  }
  return ret;
}

int bestPosition(char seed){
	if(seed == 'X')	return bestMoveP1();
	else return bestMoveP2();
}

void addSeed(char seed, int col){
	gameGrid[columnHeight[col]][col] = seed;
	++columnHeight[col];
}

void removeSeed(int col){
	--columnHeight[col];
	gameGrid[columnHeight[col]][col] = 0;
}

void initializeBoard(void){
	memset(gameGrid, 0, sizeof gameGrid);
	memset(columnHeight, 0, sizeof columnHeight);
	currentTurn = 'X';
	currentState = RUNNING;
}

GameState checkGameState(void){
	int st;
	if(isMovesLeft()==0)	return TIE;
	st = evaluate();
	switch(st){
		case 100 : return P1WIN;
		case -100 : return P2WIN;
		default : return RUNNING;
	}
}

int heightOf(int col){
	return columnHeight[col];
}
