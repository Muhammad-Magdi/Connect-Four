#include "PortFDriver.h"

void portFInit(){
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0   
}

// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06


void setPin(int pinNum, int val){
	   GPIO_PORTF_DATA_R |=(val<<pinNum);
}

int  getPinVal(int pinNum){
		return GPIO_PORTF_DATA_R | (1<<pinNum);
}

void setRedLed(){
		GPIO_PORTF_DATA_R = 0x02;
}
void clearRedLed(){
		GPIO_PORTF_DATA_R &= ~0x02;
}
void toggleRedLed(){
	GPIO_PORTF_DATA_R ^= 0x02;
}
int  getRedLed(){
		return GPIO_PORTF_DATA_R |0x02;
}


void setBlueLed(){
		GPIO_PORTF_DATA_R = 0x04;
}
void clearBlueLed(){
		GPIO_PORTF_DATA_R &= ~0x04;
}
void toggleBlueLed(){
	GPIO_PORTF_DATA_R ^= 0x04;
}
int  getBlueLed(){
		return GPIO_PORTF_DATA_R |0x04;
}

void blinkRedLed(int n){
	while(n--){
		toggleRedLed();
		Delay(30);
		toggleRedLed();
	}
}

void blinkGreenLed(int n){
	while(n--){
		toggleGreenLed();
		Delay(30);
		toggleGreenLed();
	}
}
void blinkBlueLed(int n){
	while(n--){
		toggleBlueLed();
		Delay(30);
		toggleBlueLed();
	}
}
void setGreenLed(){
		GPIO_PORTF_DATA_R = 0x08;
}
void clearGreenLed(){
		GPIO_PORTF_DATA_R &= ~0x08;
}
void toggleGreenLed(){
	GPIO_PORTF_DATA_R ^= 0x08;
}
int  getGreenLed(){
		return GPIO_PORTF_DATA_R |0x08;
}



void setYellowLed(){
		GPIO_PORTF_DATA_R = 0x0A;
}
void clearYellowLed(){
		GPIO_PORTF_DATA_R &= ~0x0A;
}
void toggleYellowLed(){
	GPIO_PORTF_DATA_R ^= 0x0A;
}
int  getYellowLed(){
		return GPIO_PORTF_DATA_R |0x0A;
}

int isSw1Pressed(){
	return !(GPIO_PORTF_DATA_R &0x10);
}
int isSw1ShortPressed(){
	int sw1_time=0;
	while(isSw1Pressed()){
		sw1_time++;
	}
	return sw1_time<727240*200/182?1:0;
}
int isSw1LongPressed(){
	int sw1_time=0;
	while(isSw1Pressed()){
		sw1_time++;
	}
	return sw1_time>727240*200/182?1:0;
}


int isSw2Pressed(){
	return !(GPIO_PORTF_DATA_R &0x01);
}
int isSw2ShortPressed(){
	int sw2_time=0;
	while(isSw2Pressed()){
		sw2_time++;
	}
	return sw2_time<727240*200/182?1:0;
}
int isSw2LongPressed(){
	int sw2_time=0;
	while(isSw2Pressed()){
		sw2_time++;
	}
	return sw2_time>727240*200/182?1:0;
}


void Delay(int val){unsigned long volatile time;
  time = 727240*200*val/182;  // 0.1sec
  while(time){
		time--;
  }
}