#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "eeprom.h"

void writeToEEPROM(unsigned int address, unsigned char value){
	unsigned char looptmp = 0;
	unsigned char u8_addrl_r = 0;
	unsigned char code *cd_longaddr;
	unsigned char xdata *xd_tmp;
	

	u8_addrl_r = address;
	
	if(u8_addrl_r < 0x80)
	{
		u8_addrl_r = 0;
	}
	else 
	{
		u8_addrl_r = 0x80;
	}

	xd_tmp = 0x280;
	cd_longaddr = ((address & 0xff00) + u8_addrl_r);	
	
	while(xd_tmp !=0x300)
	{
		*xd_tmp = *cd_longaddr;
		looptmp++;
		xd_tmp++;
		cd_longaddr++;
	}

	u8_addrl_r = address;
	
	if (u8_addrl_r < 0x80)
	{
		xd_tmp = (u8_addrl_r + 0x280);
	}
	else
	{
		xd_tmp = (u8_addrl_r + 0x200);
	}
	
	*xd_tmp = value;

	IAPAL = address;
	IAPAH = (address >> 8);
	IAPFD = 0xFF;
	set_IAPEN; 
	set_APUEN;
	IAPCN = 0x22; 		
	set_IAPGO; 

	u8_addrl_r = address;
	
	if (u8_addrl_r < 0x80)
	{
		u8_addrl_r = 0;
	}
	else
	{
		u8_addrl_r = 0x80;
	}
	
	xd_tmp = 0x280;
	IAPAL = u8_addrl_r;
	IAPAH = (address >> 8);
	set_IAPEN; 
	set_APUEN;
	IAPCN = 0x21;
	
	while(xd_tmp !=0x2FF)
	{
		IAPFD = *xd_tmp;
		set_IAPGO;
		IAPAL++;
		xd_tmp++;
	}
	
	clr_APUEN;
	clr_IAPEN;
}	


unsigned char readFromEEPROM(unsigned int code *address) {
	unsigned char value = 0;
	
	value = (*address >> 8);
	
	return value;
}