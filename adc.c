#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "adc.h"

void _init_ADC(void){
	P03_Input_Mode;	//P0.3 input mode
	set_P03DIDS;		//disconnect digital ckt
	ADCCON0&=0xF0;	//select AIN6
	ADCCON0|=0x6;
	set_ADCEN;			//Enable ADC Ckt
}
/*void adcInterrupt (void) interrupt 11 using 2{
	clr_EADC; //ADC_interrupt clear
	clr_ADCF;	//conversion_complete_bit
	uartTX("adc");
}*/
unsigned int getADCValue(void){
	unsigned int adc_value = 0x0000;
	set_ADCS;				//Start conversion	
	while(ADCS);
	clr_ADCF;
	adc_value = ADCRH;
	adc_value <<= 4;	 
	adc_value |= ADCRL;
	return adc_value;
}		

