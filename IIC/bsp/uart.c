#include "uart.h"
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"

void init_uart1(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX, 0);
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX, 0);

    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 0x10B0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX, 0x10B0);

    UART1->UCR2 &= ~(1 << 0);
    unsigned int t;
    t = UART1->UCR2;
    t |= (1 << 14) | (1 << 5) | (1 << 2) | (1 << 1);
    t &= ~((1 << 8) | (1 << 6));
    UART1->UCR2 = t;

    UART1->UCR3 |= (1 << 2);

    UART1->UFCR &= ~(5 << 7);
    UART1->UFCR |= (5 << 7);

    UART1->UBIR = 999;
    UART1->UBMR = 43402;

    UART1->UCR1 |= (1 << 0);
}

void putc(unsigned char c)
{
    while ((UART1->USR2 & (1 << 3)) == 0)
        ;
    UART1->UTXD = c;
}
void raise(int n)
{
}
unsigned char getc(void)
{
    while ((UART1->USR2 & (1 << 0)) == 0)
        ;
    return UART1->URXD & 0xFF;
}

void puts(const char *p)
{
    while (*p)
    {
        putc(*p++);
    }
    putc('\n');
}
