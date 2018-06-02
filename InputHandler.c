#include "InputHandler.h"

/* this function initializes the ports connected to the keypad */
void keyPadInit(void){
	SYSCTL->RCGCGPIO |= 0x04; /* enable clock to GPIOC */
	SYSCTL->RCGCGPIO |= 0x10; /* enable clock to GPIOE */

	KEYPAD_ROW->DIR |= 0x0F; /* set row pins 3-0 as output */
	KEYPAD_ROW->DEN |= 0x0F; /* set row pins 3-0 as digital pins */
	KEYPAD_ROW->ODR |= 0x0F; /* set row pins 3-0 as open drain */

	KEYPAD_COL->DIR &= ~0xF0; /* set column pin 7-4 as input */
	KEYPAD_COL->DEN |= 0xF0; /* set column pin 7-4 as digital pins */
	KEYPAD_COL->PUR |= 0xF0; /* enable pull-ups for pin 7-4 */
}

unsigned char getInputKey(void){
	const unsigned char keymap[4][4] = {{ '1', '2', '3', 'A'},
																			{ '4', '5', '6', 'B'},
																			{ '7', '8', '9', 'C'},
																			{ '*', '0', '#', 'D'}};
	int row, col, msk;
	while(1){
		for(row = 0 ; row < 4 ; ++row){		//for each row
			msk = 0x0F & ~(1<<row);
			KEYPAD_ROW->DATA = msk;
			//TODO Delay here
			col = KEYPAD_COL->DATA & 0xF0;
			if(col != 0xF0)	break;
		}
		if(col != 0xF0){
			col >>= 4;
			col = ~col;
			return keymap[row][col];
		}
	}
}