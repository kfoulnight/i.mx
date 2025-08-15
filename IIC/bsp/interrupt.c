#include "interrupt.h"
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
#include "core_ca7.h"

static irq_handler_t interrupt_vector_table[160];

void system_interrupt_init(void)
{
    __set_VBAR(0x87800000);
    GIC_Init();
}

void system_interrupt_register(irq_handler_t handler, int num)
{
    interrupt_vector_table[num] = handler;
}

void system_interrupt_handler(int irq)
{
    if(interrupt_vector_table[irq] != NULL)
    {
        interrupt_vector_table[irq]();
    }
}
