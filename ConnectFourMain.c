#include "tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "TExaS.h"
#include "ConnectFour.h"
#include "UserInterface.h"
#include "UARTHandler.h"

int mode, masterMode, currentTurn, nextColumn;
char gameGrid[ROWS][COLS];
int columnHeight[COLS];
char playerSeed, opponentSeed;

//Initializes the game
void initialize();
//Adds a seed into the given Column
void addSeed(char seed, int col);

int main(void){
	while(1){
		initialize();
		mode = selectMode();
		if(mode == 1){			//Single Player
			playerSeed = selectSeed();
			opponentSeed = (playerSeed == 'X' ? 'O' : 'X');
			while(checkGameState(gameGrid) == RUNNING){
				if(currentTurn == playerNumber){
					//nextColumn = take Input
					drawSeed(playerSeed, nextColumn);
					addSeed(playerSeed, nextColumn);
				}else{
					nextColumn = bestPosition(gameGrid);
					drawSeed(opponentSeed, nextColumn);
					addSeed(opponentSeed, nextColumn);
				}
				currentTurn = (currentTurn%2)+1;		//Toggle Turn
			}
		}else{							//Multi.
			masterMode = isMaster();
			if(masterMode){
			
			}else{
			
			}
		}
	}
}
