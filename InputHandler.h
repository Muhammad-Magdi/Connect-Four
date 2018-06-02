#define KEYPAD_ROW GPIOE
#define KEYPAD_COL GPIOC

/* this function initializes the ports connected to the keypad */
void keyPadInit(void);

unsigned char getInputKey(void);
