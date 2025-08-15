#include "clock.h"
#include "MCIMX6Y2.h"

void enable_clock(void)
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;   
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;   
}

void init_clock(void)
{
    /*1:初始化ARM时钟*/
    CCM->CCSR &= ~(1 << 8);
    CCM->CCSR |= (1 << 2); //arm isc24MHz
    unsigned int t;
    t = CCM_ANALOG->PLL_ARM;
    t &= ~(3 << 14);
    t |= (1 << 13);
    t &= ~(0x7F << 0);
    t |= (88 << 0);
    CCM_ANALOG->PLL_ARM = t;//1056Hz
    CCM->CACRR &= ~(7 << 0);
    CCM->CACRR |= (1 << 0);
    CCM->CCSR &= ~(1 << 2);

    /*2、设置528 、480PLL的八个PFD */
    t = CCM_ANALOG->PFD_528;
    t &= ~((0x3F << 0) | (0x3F << 8) | (0x3F << 16) | (0x3F << 24));
    t |= (27 << 0) | (16 << 8) | (24 << 16) | (32 << 24);
    CCM_ANALOG ->PFD_528 = t;

    t = CCM_ANALOG->PFD_480;
    t &= ~((0x3F << 0) | (0x3F << 8) | (0x3F << 16) | (0x3F << 24));
    t |= (12 << 0) | (16 << 8) | (17 << 16) | (19 << 24);
    CCM_ANALOG->PFD_480 = t;

    /*3设置根时钟*/
    t = CCM->CBCMR;
    t &= ~(3 << 18);
    t |= (1 << 18);
    CCM->CBCMR = t;

    t = CCM->CBCDR ;
    t &= ~(1 << 25);
    t &= ~(7 << 10);
    t |= (2 << 10);
    t &= ~(3 << 8);
    t |= (1 << 8);
    CCM->CBCDR = t;

    t = CCM->CSCMR1;
    t &= ~(1 << 6);
    t &= ~(0x3F << 0);
    CCM->CSCMR1 = t;
    enable_clock();
}
