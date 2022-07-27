void _init_UART0_(long);
void uart0WriteChar(char userData);
char uart0ReadChar(void);
void uart0TX(char *_data);
char* uart0RX(int);
int uart0available(void);
#define FSYS 16000000