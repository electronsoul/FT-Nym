#include "typecon.h"
#include <stdlib.h>

#define MAX_LEN         10   // 32767 is 6 characters with NULL terminator
#define BASE_10         10  // Print decimal format

char* toStr(unsigned int value) { //long
  char *ch = ""; //[MAX_LEN];
  
  unsigned int n = value, count = 0, i = 0, j = 1;
  do{
    n /= 10;
    ++count;
  } while (n != 0);
  
  if(count == 1){
    *(ch) = ((value % 10)+ 0x30);
    *(ch+1) = '\0';
    return ch;
  }
  if(count == 2){
    *(ch)   = (((value / 10)  % 10)+ 0x30);
    *(ch+1) = ((value % 10)+ 0x30);
    *(ch+2) = '\0';
    return ch;
  }
  //1234 count = 4 
  *(ch+count - 2) = (((value / 10)  % 10)+ 0x30);  //3
  *(ch+count - 1) = ((value % 10)+ 0x30);          //4
  *(ch+count) = '\0';                              //NULL
                  
  for(i = count - 3; i >= 0 ; i--){  //1,0
    *(ch+i) = (((value / (100*j)) % 10)+ 0x30); 
    j *= 10;
  }
  return ch;  
}
/*
char* toStr(unsigned long num) {
	int index = 0; 
  char str[ MAX_LEN ];     //6
	int n = num, count = 0;
	
	do{
		n /= 10;
		++count;
		} while (n != 0);
	index = count;
		
  str[ index ] = '\0';
  while( index-- )
  {
		str[ index ] = ( num % BASE_10 ) + '0'; 
    num /= BASE_10;
		if( num == 0 )
			break;
	}
	return str;
}
*/