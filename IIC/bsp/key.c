#include "key.h"
#include "fsl_iomuxc.h"
#include "core_ca7.h"
#include "led.h"
#include "interrupt.h"

void key_handler(void)
{
    if((GPIO1->ISR & (1 << 18)) != 0)
    {
        led_nor();
        GPIO1->ISR |= (1 << 18);
    }   
}

void init_key(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);
    GPIO1->GDIR &= ~(1 << 18);
    GPIO1->ICR2 |= (3 << 4);
    GPIO1->IMR |= (1 << 18);
    system_interrupt_register(key_handler, GPIO1_Combined_16_31_IRQn);   
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
}



int key_pressed(void)
{
    return (GPIO1->DR & (1 << 18)) == 0;
}

