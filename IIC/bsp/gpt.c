#include "gpt.h"
#include "MCIMX6Y2.h"

void reset_gpt(GPT_Type *base)
{
    base->CR |= (1 << 15);
    while((base->CR & (1 << 15)) != 0);
}

void init_gpt1(void)
{
    reset_gpt(GPT1);
    unsigned int t;
    t = GPT1->CR;
    t &= ~(7 << 26);
    t &= ~(3 << 18);
    t |= (1 << 9);
    t &= ~(7 << 6);
    t |= (1 << 6);
    t &= ~(1 << 1);
    GPT1->CR = t;

    t = GPT1->PR;
    t &= ~(0xFFF << 0);
    t |= (65 << 0);
    GPT1->PR = t;

    GPT1->CR |= (1 << 0);
}

void delay_us(unsigned int n)
{
    unsigned int counter = 0;
    unsigned int new_counter, old_couter;
    old_couter = GPT1->CNT;
    while(1)
    {
        new_counter = GPT1->CNT;
        if(new_counter != old_couter)
        {
            if(new_counter < old_couter)
            {
                counter += 0xFFFFFFFF - old_couter + new_counter;
            }
            else
            {
                counter += new_counter - old_couter;
            }
            if(counter >= n)
            {
                return;
            }
            old_couter = new_counter;
        }
    }
}

void delay_ms(unsigned int n)
{
    while(n--)
    {
        delay_us(1000);
    }
}

