#ifndef PORTF_DRIVER_H
#define PORTF_DRIVER_H

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

void setPin(int pinNum, int val);
void portFInit();
int  getPinVal(int pinNum);
void setRedLed();
void clearRedLed();
void toggleRedLed();
void setBlueLed();
void clearBlueLed();
void toggleBlueLed();
void setGreenLed();
void clearGreenLed();
void toggleGreenLed();
void setYellowLed();
void clearYellowLed();
void toggleYellowLed();
void blinkRedLed(int n);
void blinkGreenLed(int n);
void blinkBlueLed(int n);
int getRedLed();
int getYellowLed();
int getBlueLed();
int getGreenLed();
int isSw1Pressed();
int isSw1ShortPressed();
int isSw1LongPressed();
int isSw2Pressed();
int isSw2ShortPressed();
int isSw2LongPressed();
void Delay(int);
#endif