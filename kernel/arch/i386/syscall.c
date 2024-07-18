#include <kernel/idt.h>
#include <kernel/syscall_numbers.h>
#include <kernel/process.h>
#include <kernel/exec.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SYSCALL_INTERRUPT 0x80

extern void syscall_handler_asm();

uint32_t get_syscall_number() {
    uint32_t syscall_number;
    asm volatile ("movl %%eax, %0" : "=r" (syscall_number));
    return syscall_number;
}

int sys_fork() {
    return process_create(NULL);
}

void sys_exit(int status) {
    process_exit(status);
    // This function should not return
    while(1);
}

int sys_wait(uint32_t pid) {
    return process_wait(pid);
}

int sys_exec(executable_t* program) {
    if (program->size > MAX_PROGRAM_SIZE) {
        return -1;  // Program too large
    }

    // we'll just copy the code to a predefined location.
    uint32_t* code_dest = (uint32_t*)0x100000;  // 1 MB mark
    memcpy(code_dest, program->code, program->size);

    // Update the process's instruction pointer
    processes[current_pid].eip = program->entry_point + 0x100000;

    // Jump to the new code
    asm volatile ("jmp *%0" : : "r" (processes[current_pid].eip));

    // We should never reach here
    return 0;
}


void syscall_handler_c() {
    uint32_t syscall_number = get_syscall_number();
    int ret = 0;

    switch (syscall_number) {
        case SYS_FORK:
            ret = sys_fork();
            break;
        case SYS_EXIT:
            sys_exit(*(int*)(&syscall_number + 1));  // Get the status from the stack
            break;
        case SYS_WAIT:
            ret = sys_wait(*(uint32_t*)(&syscall_number + 1));  // Get the pid from the stack
            break;
        case SYS_EXEC:
            ret = sys_exec(*(executable_t**)(&syscall_number + 1));  // Get the program pointer from the stack
            break;
        default:
            printf("Unknown system call: %d\n", syscall_number);
            break;
    }

    // Set the return value in eax
    asm volatile ("movl %0, %%eax" : : "r" (ret));
}

void init_syscalls() {
    idt_set_gate(SYSCALL_INTERRUPT, (uint32_t)syscall_handler_asm, 0x08, 0x8E);
    printf("System call handler installed.\n");
}