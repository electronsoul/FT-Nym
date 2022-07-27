#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include "time.h"

/*
Based on timer3
*/

static unsigned long currentmils = 0;

void timer3_ISR(void) interrupt 16{
	clr_TF3;
	currentmils++;
}

void _init_millis_(void){
	EA = 1;
	set_ET3;
	RL3 = LOBYTE(65536 - 16050);
	RH3 = HIBYTE(65535 - 16050);
	set_TR3;
}

unsigned long millis(void){
	return currentmils;
}