#include "tm4c123gh6pm.h"
#include "TExaS.h"
#include "ConnectFour.h"
#include "UserInterface.h"
#include "UARTHandler.h"
#include "string.h"

int mode, nextColumn;
char gameGrid[ROWS][COLS];
int columnHeight[COLS];
char playerSeed, opponentSeed, currentTurn;
GameState currentState;

//Initializes the game
void initialize(void);
//Adds a seed into the given Column
void addSeed(char seed, int col);

int main(void){
	while(1){
		initialize();
		WelcomeScene();
		mode = SelectModeScene();
		if(mode == 1){			//Single Player
			playerSeed = SelectSeedScene();
			opponentSeed = (playerSeed == 'X' ? 'O' : 'X');
			while(currentState == RUNNING){
				if(currentTurn == playerSeed){
					//nextColumn = take Input
					addSeed(playerSeed, nextColumn);
				}else{
					nextColumn = bestPosition(gameGrid);
					addSeed(opponentSeed, nextColumn);
				}
				currentTurn = (currentTurn == 'X' ? 'O' : 'X');		//Toggle Turn
				currentState = checkGameState(gameGrid);
			}
		}else{							//Multi.
			if(isMaster()){
				//Choose a seed and tell the slave his seed
				playerSeed = SelectSeedScene();
				//TODO Tell slave his seed type
				while(currentState == RUNNING){
					if(currentTurn == playerSeed){
						//nextColumn = take Input
						//If the Player Entered #, run AI mode
						addSeed(playerSeed, nextColumn);
						//Tell the slave the column I played in
					}else{
						
					}
					currentTurn = (currentTurn == 'X' ? 'O' : 'X');		//Toggle Turn
					currentState = checkGameState(gameGrid);
				}
			}else{
				
			}
		}
	}
}


void initialize(void){
	memset(gameGrid, 0, sizeof gameGrid);
	memset(columnHeight, 0, sizeof columnHeight);
	currentTurn = 'X';
	currentState = RUNNING;
}

void addSeed(char seed, int col){
	gameGrid[columnHeight[col]][col] = seed;
	++columnHeight[col];
	drawSeed(seed, col);
}