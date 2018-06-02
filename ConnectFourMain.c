#include "tm4c123gh6pm.h"
#include "TExaS.h"
#include "ConnectFour.h"
#include "UserInterface.h"
#include "UARTHandler.h"
#include "string.h"
#include "InputHandler.h"

int mode, nextColumn, firstTime;
char gameGrid[ROWS][COLS];
int columnHeight[COLS];
char playerSeed, opponentSeed, currentTurn, tmpChar;
GameState currentState;

//Initializes the game
void initialize(void);
//Adds a seed into the given Column
void addSeed(char seed, int col);
void confirm(void);
void sendAndWaitConfirmation(unsigned char);
int validColumn(unsigned char);

int main(void){
	UARTInit();
	keyPadInit();
	while(1){
		initialize();
		WelcomeScene();
		mode = SelectModeScene();
		if(mode == 1){			//Single Player
			
			playerSeed = SelectSeedScene();
			
			while(currentState == RUNNING){
				if(currentTurn == playerSeed){
					
					while(!validColumn(nextColumn))
						nextColumn = getInputKey();
					
					if(nextColumn == '#')	nextColumn = bestPosition(gameGrid, currentTurn);
					addSeed(currentTurn, nextColumn);
				}else{
					nextColumn = bestPosition(gameGrid, currentTurn);
					addSeed(currentTurn, nextColumn);
				}
				currentTurn = (currentTurn == 'X' ? 'O' : 'X');		//Toggle Turn
				currentState = checkGameState(gameGrid);
			}
			
		}else{							//Multi.
			if(isMaster()){
				//HandShake as a master
				connectingScene();
				sendAndWaitConfirmation(17);
				//Choose a seed and tell the slave
				playerSeed = SelectSeedScene();
				sendAndWaitConfirmation(playerSeed == 'X' ? 31 : 32);
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
				connectingScene();
				do{
					tmpChar = receive();
				}while(tmpChar != 17);
				send(200);
				
			}
		}
	}
}

void initialize(void){
	memset(gameGrid, 0, sizeof gameGrid);
	memset(columnHeight, 0, sizeof columnHeight);
	currentTurn = 'X';
	currentState = RUNNING;
	firstTime = 1;
}

void addSeed(char seed, int col){
	gameGrid[columnHeight[col]][col] = seed;
	drawSeed(seed, col, columnHeight[col]);
	++columnHeight[col];
}

void confirm(void){
	
}

void sendAndWaitConfirmation(unsigned char c){
	firstTime = 1;
	do{
		send(c);
		if(!firstTime)	Delay100ms(3);
		firstTime = 0;
	}while(receive()!=200);
}

int validColumn(unsigned char col){
	return (col == '#' || (col <= '0' && col <= '9' && columnHeight[col-'0'] < ROWS));
}