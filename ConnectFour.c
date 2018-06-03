#include <stdio.h>
#include <stdlib.h>
#include "ConnectFour.h"

char player1 = 'X', player2 = 'O';
int col[COLS];
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
    if(col[i] < ROWS)
      return 1;
  }
  return 0;
}

int evaluate(char board[ROWS][COLS]){
	int i, j;
  for(i=0; i<ROWS; i++){
    for(j=0; j<COLS; j++){
      if(j<4 && board[i][j]==board[i][j+1] && board[i][j]==board[i][j+2] && board[i][j]==board[i][j+3]){
        if(board[i][j] == player1)
          return 100;
        else if(board[i][j] == player2)
          return -100;
      }
      if(i<3 && board[i][j]==board[i+1][j] && board[i][j]==board[i+2][j] && board[i][j]==board[i+3][j]){
        if(board[i][j] == player1)
          return 100;
        else if(board[i][j] == player2)
          return -100;
      }
      if(i<3 && j<4 && board[i][j]==board[i+1][j+1] && board[i][j]==board[i+2][j+2] && board[i][j]==board[i+3][j+3]){
        if(board[i][j] == player1)
          return 100;
        else if(board[i][j] == player2)
          return -100;
      }
      if(i>2 && j<4 && board[i][j]==board[i-1][j+1] && board[i][j]==board[i-2][j+2] && board[i][j]==board[i-3][j+3]){
        if(board[i][j] == player1)
          return 100;
        else if(board[i][j] == player2)
          return -100;
      }
    }
  }
  return 0;
}

int minimax(int depth, int isMax, int alpha, int beta, char board[ROWS][COLS]){
  int score = evaluate(board), i;
  if(depth == 10)
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
      if(col[i] < ROWS){
        board[col[i]++][i] = player1;
        best = max(best, minimax(depth+1, 2, alpha, beta, board));
        alpha = max(alpha, best);
        board[--col[i]][i] = '-';
      }
      if(beta <= alpha)
        break;
    }
    return best;
  }
  else{
    int best = INF;
    for(i=0; i<COLS; i++){
      if(col[i] < ROWS){
        board[col[i]++][i] = player2;
        best = min(best, minimax(depth+1, 1, alpha, beta, board));
        beta = min(beta, best);
        board[--col[i]][i] = '-';
      }
      if(beta <= alpha)
        break;
    }
    return best;
  }
}

int bestMoveP1(char board[ROWS][COLS]){
  int bestVal = -INF;
  int ret = -1;
	int i;
	int moveVal;
  for(i=0; i<COLS; i++){
    if(col[i] < ROWS){
      board[col[i]++][i] = player1;
      moveVal = minimax(0, 2, -INF, INF, board);
      board[--col[i]][i] = '-';
      if(moveVal > bestVal){
        ret = i;
        bestVal = moveVal;
      }
    }
  }
  return ret;
}

int bestMoveP2(char board[ROWS][COLS]){
  int bestVal = INF;
  int ret = -1;
	int i;
	int moveVal;
	
  for(i=0; i<COLS; i++){
    if(col[i] < ROWS){
      board[col[i]++][i] = player2;
      moveVal = minimax(0, 1, -INF, INF, board);
      board[--col[i]][i] = '-';
      if(moveVal < bestVal){
        ret = i;
        bestVal = moveVal;
      }
    }
  }
  return ret;
}

int bestPosition(char grid[ROWS][COLS], char seed){
	if(seed == 'X')	return bestMoveP1(grid);
	else return bestMoveP2(grid);
}