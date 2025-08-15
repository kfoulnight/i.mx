#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

typedef void (*irq_handler_t)(void);
extern void system_interrupt_init(void);
extern void system_interrupt_register(irq_handler_t handler, int num);

#endif