#ifndef _KERNEL_KHEAP_H
#define _KERNEL_KHEAP_H

#include <stdint.h>

#define KHEAP_START         0xC0000000
#define KHEAP_INITIAL_SIZE  0x100000

uint32_t kmalloc(uint32_t size);
uint32_t kmalloc_a(uint32_t size);  // page aligned
uint32_t kmalloc_p(uint32_t size, uint32_t *phys);  // returns a physical address
uint32_t kmalloc_ap(uint32_t size, uint32_t *phys);  // page aligned and returns a physical address

void kfree(void *p);

#endif