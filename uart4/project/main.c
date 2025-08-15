#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "core_ca7.h"
#include "interrupt.h"
#include "clock.h"
#include "epit.h"
#include "gpio.h"
#include "gpt.h"
#include "uart.h"
#include "stdio.h"
#include "string.h"

void delay(unsigned int n)
{
    while (n--)
        ;
}

int main(void)
{
    char rcv_buffer[100];
    init_clock();
    system_interrupt_init();
    init_beep();
    init_led();
    init_key();
    // init_epit1();
    init_gpt1();
    init_uart1();
    while (1)
    {
        //    if(key_pressed())
        //    {
        //         beep_on();
        //         led_on();
        //    }
        //    else
        //    {
        //         beep_off();
        //         led_off();
        //    }
        // led_nor();
        // delay(0x7FFFF);
        // puts("hello world!");
        // delay_ms(1000);
        // unsigned char c;
        // c = getc();
        // if( 'A' ==c )
        // {
        //     puts("hello world!");
        // }
        // else if('B' == c)
        // {
        //    puts("nihaowa!!");
        // }
        // else
        // {
        //     puts("error!");
        // }

        // int i, j;
        // scanf("%d%d", &i, &j);
        // printf("%d + %d = %d\n", i, j, i + j);
        // int *p = NULL;
        // printf("%lu\n",sizeof(p));
        // delay_ms(1000);
        // int i = 1;
        // char *p = (char *)&i;
        // printf("%d\n",*p);
        // delay_ms(1000);
        scanf("%s", &rcv_buffer);
        if (strncmp(rcv_buffer, "ledon", 5) == 0)
        {
            printf("---ok---\n");
            led_on();
        }
        else if (strncmp(rcv_buffer, "ledoff", 6) == 0)
        {
            printf("---ok---\n");
            led_off();
        }
        else if (strncmp(rcv_buffer, "beepoff", 7) == 0)
        {
            beep_off();
            printf("---ok---\n");
        }
        else if (strncmp(rcv_buffer, "beepon", 6) == 0)
        {
            beep_on();
            printf("---ok---\n");
        }
    }
}