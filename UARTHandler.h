#ifndef UART_HANDLER_H
#define UART_HANDLER_H

void UARTInit(void);

//Sends a char through the UART
void send(unsigned char c);

//Listens and receives a char through out the UART
unsigned char receive(void);

#endif