void UARTInit(void);

//Sends a char through the UART
void send(unsigned char c);

//Listens and receives a char through out the UART
unsigned char receive(void);

#include "UARTHandler.c"
