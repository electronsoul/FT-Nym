#include "crc.h"
#include "typecon.h"

int getCRC(int mesg){ 
	int i = 0;
	int temp = 0, rem = 0, count = 0, n = 0;
	
	int CRCREG = 0x0;
	temp = mesg;
	
  n = mesg;
  do{
    n /= 2;
    ++count;
  } while (n != 0);
  
	for(i = 0; i < count; i++){		
		temp &= 0x1;
		if(temp ^ (CRCREG & 0x1)){
			CRCREG >>= 1;
			CRCREG ^= CRCDIVISOR;
		}
		else{
      CRCREG >>= 1;
    }
		temp = mesg;
		temp >>= 1;  
		mesg >>= 1;
	}		
	
	rem = CRCREG;
	
	return rem;
}

