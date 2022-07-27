/*
01111110 00000000 00000000 00000000 10000001
|      | |      | |      | |      | |______|__Stop byte
|      | |      | |      | |______|___________8_bit CRC
|      | |      | |______|____________________Payload byte
|      | |______|_____________________________Packet ID (0 by default)
|______|______________________________________Start byte (constant)
*/

/*
CRC-8-CCITT
x^8 + x^2 + x^1 + 1 
Polynomial Representation = 0x07
*/

#define CRC_ERROR 0
#define PREAMBLE_SIZE 2
#define POSTAMBLE_SIZE 2
#define START_BYTE '~'
#define STOP_BYTE '!'
#define CRCDIVISOR 0x32     

typedef struct {
	int pktID;
	char pktDATA;
}pkt_t;

int getCRC(int);
