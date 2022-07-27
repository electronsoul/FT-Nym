#define FLASH_BASE_ADDRESS 0x3700

void writeToEEPROM(unsigned int address, unsigned char value);
unsigned char readFromEEPROM(unsigned int code *address);