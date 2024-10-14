#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/process.h>
#include <kernel/idt.h>
#include <kernel/syscall.h>
#include <kernel/timer.h>
#include <kernel/paging.h>

extern void test_process_management(void);
extern void test_syscalls(void);

void kernel_main(void) {
    terminal_initialize();
    printf("Hello, kernel World!\n");

    idt_install();
    printf("IDT installed.\n");

    init_syscalls();
    printf("System calls initialized.\n");

    paging_init();
    printf("Paging initialized.\n");

    timer_install();
    printf("Timer installed.\n");

    process_init();
    printf("Process management initialized.\n");

    // Enable paging
    uint32_t cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging!
    asm volatile("mov %0, %%cr0":: "r"(cr0));

    printf("Paging enabled.\n");

    test_process_management();
    test_syscalls();

    printf("Kernel main completed.\n");

    // Halt the CPU
    while(1) {
        asm volatile("hlt");
    }
}