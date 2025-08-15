#include "led.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "gpio.h"

void init_led(void)
{
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10B0);
    // GPIO1->GDIR |= (1 << 3);
    // led_off();
    gpio_configt_t t = 
    {
        .pin_direction = gpio_direction_output,
        .default_vaule = 1
    };
    init_gpio(GPIO1, 3, &t);
}


void led_off(void)
{
    write_gpio(GPIO1, 3, 1);
}

void led_on(void)
{
    write_gpio(GPIO1, 3, 0);
}

void led_nor(void)
{
    write_gpio(GPIO1, 3, !read_gpio(GPIO1, 3));
}
