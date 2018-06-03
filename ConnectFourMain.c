#include "tm4c123gh6pm.h"
#include "TExaS.h"
#include "Nokia5110.h"
#include "UARTHandler.h"
#include "InputHandler.h"
#include "ConnectFour.h"
#include "UserInterface.h"
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
		welcomeScene();
		mode = selectModeScene();
		if(mode == 1){			//Single Player
			
			playerSeed = selectSeedScene();
			drawEmptyGrid();
			while(currentState == RUNNING){
				if(currentTurn == playerSeed){
					
					do{
						nextColumn = getInputKey();
					}while(!validColumn(nextColumn));
										
					if(nextColumn == '#')	nextColumn = bestPosition(gameGrid, currentTurn);
					addSeed(currentTurn, nextColumn);
				}else{
					nextColumn = bestPosition(gameGrid, currentTurn);
					addSeed(currentTurn, nextColumn);
				}
				currentTurn = (currentTurn == 'X' ? 'O' : 'X');		//Toggle Turn
				currentState = checkGameState(gameGrid);
			}
			stateScene(currentState);
		}else{							//Multi.
			if(MSScene() == 1){
				//HandShake as a master
				connectingScene();
				sendAndWaitConfirmation(17);
				//Choose a seed and tell the slave
				playerSeed = selectSeedScene();
				sendAndWaitConfirmation(playerSeed == 'X' ? 31 : 32);
				drawEmptyGrid();
				while(currentState == RUNNING){
					if(currentTurn == playerSeed){
						
						do{
							nextColumn = getInputKey();
						}while(!validColumn(nextColumn));
							
						if(nextColumn == '#')	nextColumn = bestPosition(gameGrid, currentTurn);
						addSeed(currentTurn, nextColumn);
						send(nextColumn);
						currentState = checkGameState(gameGrid);
						switch(currentState){
							case RUNNING : sendAndWaitConfirmation(20); break;
							case P1WIN : case P2WIN : sendAndWaitConfirmation(21); break;
							default : sendAndWaitConfirmation(23);
						}
					}else{
						nextColumn = receive();
						while(!validColumn(nextColumn))
						{
							send(24);
							nextColumn = receive();
						}
						addSeed(currentTurn, nextColumn);

						currentState = checkGameState(gameGrid);
						switch(currentState){
							case RUNNING : sendAndWaitConfirmation(20); break;
							case P1WIN : case P2WIN : sendAndWaitConfirmation(22); break;
							default : sendAndWaitConfirmation(23);
						}
					}
					currentTurn = (currentTurn == 'X' ? 'O' : 'X');		//Toggle Turn
					//currentState = checkGameState(gameGrid);
				}
				stateScene(currentState);
			}else{
				connectingScene();
				do{
					tmpChar = receive();
				}while(tmpChar != 17);
				send(200);
				tmpChar = receive();
				send(200);
				playerSeed = (tmpChar == 31 ?  'O' : 'X');
				tmpChar = (tmpChar == 31 ? 2:1);
				displaySlaveSeed(tmpChar);
				Delay100ms(1);
				drawEmptyGrid();
				while(currentState == RUNNING){
					if(currentTurn == playerSeed){
						do {
							nextColumn = getInputKey();
							send (nextColumn);
							tmpChar = receive();
						}
						while(tmpChar==24);
						addSeed(currentTurn, nextColumn);
						
						if (tmpChar == 22 && playerSeed =='X') currentState =P1WIN ;
						else if (tmpChar ==22 &&playerSeed =='O') currentState =P2WIN ;
						else if (tmpChar ==23) currentState =TIE;
						send(200);
					}
					else 
					{
						nextColumn = receive ();
						addSeed(currentTurn, nextColumn);
						tmpChar = receive();
						if (tmpChar == 21 && playerSeed =='X') currentState =P2WIN ;
						else if (tmpChar ==21 && playerSeed =='O') currentState =P1WIN ;
						else if (tmpChar ==23) currentState =TIE;
						send(200);
						
					}
					currentTurn = (currentTurn == 'X' ? 'O' : 'X');		//Toggle Turn

				}
				stateScene(currentState);

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
		if(!firstTime)	Delay100ms(10);
		firstTime = 0;
	}while(receive()!=200);
}

int validColumn(unsigned char col){
	return (col == '#' || (col <= '1' && col <= '0'+COLS && columnHeight[col-'0'-1] < ROWS));
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
