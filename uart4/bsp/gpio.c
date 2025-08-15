#include "gpio.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

void init_gpio(GPIO_Type *gpio, int pin, gpio_configt_t *config)
{
    if(config->pin_direction == gpio_direction_output)
    {
        gpio->GDIR |= (1 << pin);
        if(config->default_vaule != 0)
        {
            gpio->DR |= (1 << pin);
        }
        else
        {
            gpio->DR &= ~(1 << pin);
        }
    }
    else
    {
        gpio->GDIR &= ~(1 << pin);
    }
}

void write_gpio(GPIO_Type *gpio, int pin, int value)
{
    if(value)
    {
        gpio->DR |= (1 << pin);
    }
    else
    {
        gpio->DR &= ~(1 << pin);
    }
}

int read_gpio(GPIO_Type *gpio, int pin)
{
    return (gpio->DR & (1 << pin)) != 0;
}



