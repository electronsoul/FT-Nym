#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "uart0.h"
#include <string.h>

#define buflen 6
static char inputDataBuffer;
static unsigned long pm = 0, cm = 0;
int flag = 0;

void uart0_ISR(void) interrupt 4{
	if(RI == 1){
		RI = 0;
			inputDataBuffer = SBUF;
			flag = 1;
	}
}

int uart0available(void){
	return flag;
}
void _init_UART0_(long baud)	{   
	long reloadValue = (256 - (16000000/(32*baud)));
	EA = 1;
	//ES = 1;

	/*Set GPIO pins for UART*/
	P06_Quasi_Mode;		
	P07_Quasi_Mode;
	
	/*Configure UART*/
	SCON = (0x70);	//UART0 Mode1,SM2=1,REN=1
	/*Configure Timer 1*/
	clr_ET1;				//Disable timer 1 interrupts
	TMOD |= (0x20);	//Timer1 Gate=0,TimerMode,Mode1(8bit_auto-reload)
	set_T1M; 				//system clock as Timer1 src
	//clr_BRCK; 		//select Timer1 as UART0 Clk Src
	//clr_SMOD;		  //UART0 Double Rate Enable
	//set_SMOD0;		//framing error flag access enable
	TH1 = reloadValue;		//Timer 1 reload value
	/*Enable Timer 1*/
	set_TR1;	
}


void uart0WriteChar(char userData) { 
	TI = 0;
	SBUF = userData;
	while(TI==0);
}	

char uart0ReadChar(void) {
	char inputData;
	while (!RI);
  inputData = SBUF;
  RI = 0;
	return inputData;
	
	/*
	if(flag == 1){
		flag = 0;
		return inputDataBuffer;
	}
	return '\0'; 
	*/
}
char* uart0RX(int bytes){
	char str[10];
	int i = 0;
	for (i = 0; i < bytes; i++){
		str[i] = uart0ReadChar();
	}
	str[i] = '\0';
	return str;
}

void uart0TX(char *_data){
	while(*_data != NULL){
		uart0WriteChar(*_data);
		_data++;
	}
}
