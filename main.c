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
