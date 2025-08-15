#include "epit.h"
#include "MCIMX6Y2.h"
#include "interrupt.h"
#include "core_ca7.h"
#include "led.h"

void epit1_interrupt_handler(void)
{
    if((EPIT1->SR & (1 << 0)) != 0)
    {
        led_nor();
        EPIT1->SR |= (1 << 0);       
    }
}

void init_epit1(void)
{
    unsigned int t;
    t = EPIT1->CR;
    t &= ~(3 << 24);
    t |= (1 << 24);
    t |= (1 << 17);
    t &= ~(0xFFF << 4);
    t |= (65 << 4);
    t |= (1 << 3) | (1 << 2) | (1 << 1);
    EPIT1->CR = t;

    EPIT1->LR |= 1000000;//0001 1010 1111 11111 1111 11111
    EPIT1->CMPR = 0;
    EPIT1->CNR = 1000000;

    EPIT1->CR |= (1 << 0);

    system_interrupt_register(epit1_interrupt_handler, EPIT1_IRQn);
    GIC_EnableIRQ(EPIT1_IRQn);
    GIC_SetPriority(EPIT1_IRQn, 0);
}



