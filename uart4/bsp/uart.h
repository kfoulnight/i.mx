#ifndef _UART_H_
#define _UART_H_

extern void init_uart1(void);
extern void putc(unsigned char c);
extern void puts(const char *p);
extern unsigned char getc(void);

#endif
