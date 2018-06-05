#include "InputHandler.h"
#include "tm4c123gh6pm.h"
#include "TExaS.h"
#include "PortFDriver.h"

/* this function initializes the ports connected to the keypad */
void keyPadInit(void){
	SYSCTL_RCGC2_R |= 0x02; /* enable clock to GPIOB */
	SYSCTL_RCGC2_R |= 0x10; /* enable clock to GPIOE */

	GPIO_PORTE_DIR_R |= 0x0F; /* set row pins 3-0 as output */
	GPIO_PORTE_DEN_R |= 0x0F; /* set row pins 3-0 as digital pins */
	GPIO_PORTE_ODR_R |= 0x0F; /* set row pins 3-0 as open drain */

	GPIO_PORTB_DIR_R &= ~0x0F; /* set column pin 3-0 as input */
	GPIO_PORTB_DEN_R |= 0x0F; /* set column pin 3-0 as digital pins */
	GPIO_PORTB_PUR_R |= 0x0F; /* enable pull-ups for pin 3-0 */
}

unsigned char getInputKey(void){
	const unsigned char keymap[4][4] = {{ '1', '2', '3', 'A'},
																			{ '4', '5', '6', 'B'},
																			{ '7', '8', '9', 'C'},
																			{ '*', '0', '#', 'D'}};
	
	int row, col, msk;
	GPIO_PORTB_DATA_R = 0x0F ;

	while(1){
		for(row = 0 ; row < 4 ; ++row){		//for each row
			msk = 0x0F & ~(1<<row);
			GPIO_PORTE_DATA_R = msk;
			col = col *100 *3*2;
			delayUs(10);
			//GPIO_PORTF_DATA_R = GPIO_PORTE_DATA_R & 0X0F;
			col = GPIO_PORTB_DATA_R & 0x0F;
			if(col != 0x0F){
				//toggleBlueLed();
				break;
			}
		}
		if(col != 0x0F){
			if (col == 0x07) col = 0; 				/* key in column 0 */
			else if (col == 0x0B) col = 1; 		/* key in column 1 */
			else if (col == 0x0D) col = 2; 		/* key in column 2 */
			else if (col == 0x0E) col = 3; 		/* key in column 3 */
			GPIO_PORTB_DATA_R = 0xF0 ;
			GPIO_PORTE_DATA_R = 0x0F ;
			return keymap[row][col];
		}
	}
}


void delayUs(int n){
	int i, j;
	for(i = 0 ; i < n; i++)
		for(j = 0; j < 3; j++){} /* do nothing for 1 us */
}