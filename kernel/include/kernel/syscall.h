#ifndef _KERNEL_SYSCALL_H
#define _KERNEL_SYSCALL_H

#include <stdint.h>

void init_syscalls();
uint32_t get_syscall_number();

#endif