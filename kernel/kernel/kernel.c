#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/process.h>
#include <kernel/idt.h>
#include <kernel/syscall.h>
#include <kernel/timer.h>
#include "../tests/process/process_test.c"
#include "../tests/syscall/syscall_test.c"

extern void test_process_management(void);
extern void test_syscalls(void);

void kernel_main(void) {
    terminal_initialize();
    printf("Hello, kernel World!\n");

    idt_install();
    printf("IDT installed.\n");

    init_syscalls();
    printf("System calls initialized.\n");

    timer_install();
    printf("Timer installed.\n");

    process_init();
    printf("Process management initialized.\n");

    test_process_management();
    test_syscalls();

    printf("Kernel main completed.\n");

    // Halt the CPU
    while(1) {
        asm volatile("hlt");
    }
}