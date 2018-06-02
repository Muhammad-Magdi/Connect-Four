#include "InputHandler.h"
#include "tm4c123gh6pm.h"
#include "TExaS.h"

/* this function initializes the ports connected to the keypad */
void keyPadInit(void){
	SYSCTL_RCGC2_R |= 0x04; /* enable clock to GPIOC */
	SYSCTL_RCGC2_R |= 0x10; /* enable clock to GPIOE */

	GPIO_PORTE_DIR_R |= 0x0F; /* set row pins 3-0 as output */
	GPIO_PORTE_DEN_R |= 0x0F; /* set row pins 3-0 as digital pins */
	GPIO_PORTE_ODR_R |= 0x0F; /* set row pins 3-0 as open drain */

	GPIO_PORTC_DIR_R &= ~0xF0; /* set column pin 7-4 as input */
	GPIO_PORTC_DEN_R |= 0xF0; /* set column pin 7-4 as digital pins */
	GPIO_PORTC_PUR_R |= 0xF0; /* enable pull-ups for pin 7-4 */
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
			GPIO_PORTE_DATA_R = msk;
			//TODO Delay here
			col = GPIO_PORTC_DATA_R & 0xF0;
			if(col != 0xF0)	break;
		}
		if(col != 0xF0){
			col >>= 4;
			col = ~col;
			return keymap[row][col];
		}
	}
}
