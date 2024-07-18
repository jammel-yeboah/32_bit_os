#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/process.h>
#include <kernel/idt.h>
#include <kernel/syscall.h>
#include <kernel/syscall_numbers.h>

void test_fork_and_wait(void) {
    printf("Before fork. PID: %d\n", process_get_current());
    
    int pid = 0;
    asm volatile ("int $0x80" : "=a" (pid) : "a" (SYS_FORK));
    
    if (pid == 0) {
        printf("Child process. PID: %d\n", process_get_current());
        asm volatile ("int $0x80" : : "a" (SYS_EXIT), "b" (42));
    } else {
        printf("Parent process. Child PID: %d\n", pid);
        int status = 0;
        asm volatile ("int $0x80" : "=a" (status) : "a" (SYS_WAIT), "b" (pid));
        printf("Child exited with status: %d\n", status);
    }
}

void kernel_main(void) {
    terminal_initialize();
    printf("Hello, kernel World!\n");

    idt_install();
    printf("IDT installed.\n");

    init_syscalls();

    process_init();
    int pid = process_create(test_fork_and_wait);
    process_set_current(pid);
    printf("Created initial process with PID %d\n", pid);

    test_fork_and_wait();

    printf("Kernel main completed.\n");
}