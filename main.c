#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

#include "uart0.h"
#include "stdint.h"
#include "typecon.h"
#include "crc.h"
#include "eeprom.h"
#include "I2C.h"

#include <stdlib.h>
#include <string.h>

void setup(void){
	char buf[] = "Finance M";
	_init_UART0_(2400);
	writeToEEPROM(14081 + 1, buf[0]);
	Timer0_Delay1ms(100);
	
	writeToEEPROM(14081 + 2, buf[1]);
	Timer0_Delay1ms(100);
	
  writeToEEPROM(14081 + 3, buf[2]);
	Timer0_Delay1ms(100);
	
  writeToEEPROM(14081 + 4, buf[3]);
	Timer0_Delay1ms(100);
	
  writeToEEPROM(14081 + 5, buf[4]);
	Timer0_Delay1ms(100);
	
  writeToEEPROM(14081 + 6, buf[5]);
	Timer0_Delay1ms(100);
	
	writeToEEPROM(14081 + 7, buf[6]);
	Timer0_Delay1ms(100);
	
	writeToEEPROM(14081 + 8, buf[7]);
	Timer0_Delay1ms(100);
	
	writeToEEPROM(14081 + 9, buf[8]);
	Timer0_Delay1ms(100);
}

void getDataFromPC(void){
	
}

void sendDataToPC(void){
	unsigned char pktdata;
	static unsigned int *temp = 0;
	uart0WriteChar('~');
	pktdata = readFromEEPROM(temp);
	uart0WriteChar(pktdata);    
	uart0WriteChar('>');
	temp++;
}

void main(void){
	int i = 0;
	setup();
	while(1){
		for(i = 0; i < 10 ; i++)
			getDataFromPC(); //Reading 10 bytes from PC-HOST
		//for(i = 0; i < 10 ; i++)
		{
			//sendDataToPC(); //Sending 10 bytes to PC-HOST
		}
	}
}