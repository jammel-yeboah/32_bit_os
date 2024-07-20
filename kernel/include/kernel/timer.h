#ifndef _KERNEL_TIMER_H
#define _KERNEL_TIMER_H

#include <stdint.h>
#include <kernel/idt.h>

void timer_handler(struct regs *r);
void timer_install();
uint32_t timer_get_tick();

#endif