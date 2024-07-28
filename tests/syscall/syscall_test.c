#include <kernel/syscall.h>
#include <stdio.h>

#define SYS_TEST 10  // Arbitrary number for our test syscall

int sys_test(int arg) {
    printf("Test system call received with argument: %d\n", arg);
    return arg * 2;
}

void test_syscalls(void) {
    printf("Starting system call test...\n");

    // Register our test system call
    register_syscall(SYS_TEST, sys_test);

    // Invoke the system call
    int result;
    asm volatile ("int $0x80" : "=a" (result) : "a" (SYS_TEST), "b" (21));

    printf("System call result: %d\n", result);
    printf("System call test completed.\n");
}