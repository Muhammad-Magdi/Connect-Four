#include "tm4c123gh6pm.h"
#include "TExaS.h"
#include "Nokia5110.h"
#include "UARTHandler.h"
#include "PortFDriver.h"
#include "InputHandler.h"
#include "ConnectFour.h"
#include "UserInterface.h"
#include "InputHandler.h"

int mode, nextColumn;
char playerSeed, tmpChar, turn;
GameState state;

//Initializes the game
void sendAndWaitConfirmation(unsigned char);
int validColumn(unsigned char);
char readValidKey(void);

int main(void){
	
	UARTInit();
	keyPadInit();
	NokiaInit();
	portFInit();
	while(1){
		initializeBoard();
		welcomeScene();
		Delay100ms(3);
		state =RUNNING;
		turn = 'X' ;
		
		mode = selectModeScene();
		if(mode == 1){			//Single Player
			Delay100ms(3);
			playerSeed = selectSeedScene();
			drawEmptyGrid();
			while(state == RUNNING){
				if(turn == playerSeed){
					nextColumn = readValidKey();
					if(nextColumn == '#')		nextColumn = bestPosition(turn);
					else nextColumn -= 0x30;		//char to int
					drawSeed(turn, nextColumn, heightOf(nextColumn));
					addSeed(turn, nextColumn);
				}else{
					nextColumn = bestPosition(turn);
					drawSeed(turn, nextColumn, heightOf(nextColumn));
					addSeed(turn, nextColumn);
				}
				turn = (turn == 'X' ? 'O' : 'X');		//Toggle Turn
				state = checkGameState();
			}
			Delay100ms(20);			//Two Seconds before printing final state
			stateScene(state, playerSeed);
			Delay100ms(20);			//Two Seconds after printing final state			
		}else{							//Multi.
			if(MSScene() == 1){
				//HandShake as a master
				connectingScene();
				sendAndWaitConfirmation(17);
				//Choose a seed and tell the slave
				playerSeed = selectSeedScene();
				sendAndWaitConfirmation(playerSeed == 'X' ? 31 : 32);
				drawEmptyGrid();
				while(state == RUNNING){
					if(turn == playerSeed){
						nextColumn = readValidKey();
						//nextColumn = '#';
						if(nextColumn == '#')	nextColumn = bestPosition(turn);
						else nextColumn -= 0x30;
						drawSeed(turn, nextColumn, heightOf(nextColumn));
						addSeed(turn, nextColumn);
						send(nextColumn);
						state = checkGameState();
						switch(state){
							case RUNNING : sendAndWaitConfirmation(20); break;
							case P1WIN : case P2WIN : sendAndWaitConfirmation(21); break;
							default : sendAndWaitConfirmation(23);
						}
					}else{
						nextColumn = receive();
						while(!validColumn(nextColumn))
						{
							send(24);						//Invalid move
							nextColumn = receive();
						}
						drawSeed(turn, nextColumn, heightOf(nextColumn));
						addSeed(turn, nextColumn);

						state = checkGameState();
						switch(state){
							case RUNNING : sendAndWaitConfirmation(20); break;
							case P1WIN : case P2WIN : sendAndWaitConfirmation(22); break;
							default : sendAndWaitConfirmation(23);
						}
					}
					turn = (turn == 'X' ? 'O' : 'X');		//Toggle Turn
					state = checkGameState();
				}
				Delay100ms(20);			//Two Seconds before printing final state
				stateScene(state, playerSeed);
				Delay100ms(20);			//Two Seconds after printing final state		
			}else{
				connectingScene();
				do{
					tmpChar = receive();
				}while(tmpChar != 17);			//Wait to find a master
				send(200);									//Confirm
				tmpChar = receive();				//Masters Seed
				send(200);									//Confirm
				playerSeed = (tmpChar == 31 ?  'O' : 'X');
				tmpChar = (tmpChar == 31 ? 2:1);
				displaySlaveSeed(tmpChar);
				Delay100ms(3);
				drawEmptyGrid();
				while(state == RUNNING){
					if(turn == playerSeed){
						do {
							nextColumn = readValidKey() - 0x30;
							send (nextColumn);
							tmpChar = receive();
						}while(tmpChar==24);		//While it's invalid
						//nextColumn = '#';
						drawSeed(turn, nextColumn, heightOf(nextColumn));
						addSeed(turn, nextColumn);
						
						if (tmpChar == 22 && playerSeed =='X') state =P1WIN ;
						else if (tmpChar ==22 &&playerSeed =='O') state =P2WIN ;
						else if (tmpChar ==23) state =TIE;
						send(200);
					}
					else 
					{
						nextColumn = receive ();
						drawSeed(turn, nextColumn, heightOf(nextColumn));
						addSeed(turn, nextColumn);
						tmpChar = receive();
						if (tmpChar == 21 && playerSeed =='X') state =P2WIN ;
						else if (tmpChar ==21 && playerSeed =='O') state =P1WIN ;
						else if (tmpChar ==23) state =TIE;
						send(200);
					}
					turn = (turn == 'X' ? 'O' : 'X');		//Toggle Turn
				}
				Delay100ms(20);			//Two Seconds before printing final state
				stateScene(state, playerSeed);
				Delay100ms(20);			//Two Seconds after printing final state		
			}
		}
	}
}

void sendAndWaitConfirmation(unsigned char c){
	int firstTime = 1;
	do{
		send(c);
		if(!firstTime)	Delay100ms(10);
		firstTime = 0;
	}while(receive()!=200);
}

int validColumn(unsigned char col){
	return (col == '#' || (col >= 0x30 && col <= (unsigned char)0x30+COLS && heightOf(col-0x30-1) < ROWS));
}

char readValidKey(void){
	do{
		Delay100ms(10);
		nextColumn = getInputKey();
	}while(!validColumn(nextColumn));
	return nextColumn;
}