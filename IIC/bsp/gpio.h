#ifndef _GPIO_H_
#define _GPIO_H_
#include "MCIMX6Y2.h"

typedef enum
{
    gpio_direction_input,
    gpio_direction_output
}gpio_direction_t;


typedef struct 
{
    gpio_direction_t pin_direction;
    int default_vaule;
}gpio_configt_t;

extern void init_gpio(GPIO_Type *gpio, int pin, gpio_configt_t *config);
extern void write_gpio(GPIO_Type *gpio, int pin, int value);
extern int read_gpio(GPIO_Type *gpio, int pin);




#endif
