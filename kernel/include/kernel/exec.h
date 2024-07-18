#ifndef _KERNEL_EXEC_H
#define _KERNEL_EXEC_H

#include <stdint.h>

#define MAX_PROGRAM_SIZE 1024

typedef struct {
    uint32_t entry_point;
    uint32_t size;
    uint8_t code[MAX_PROGRAM_SIZE];
} executable_t;

int sys_exec(executable_t* program);

#endif