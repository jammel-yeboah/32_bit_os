#include <kernel/process.h>
#include <kernel/timer.h>
#include <stdio.h>

void test_process1(void) {
    for (int i = 0; i < 5; i++) {
        printf("Process 1: %d\n", i);
        for (volatile int j = 0; j < 1000000; j++); // Simple delay
    }
    process_exit(0);
}

void test_process2(void) {
    for (int i = 0; i < 5; i++) {
        printf("Process 2: %d\n", i);
        for (volatile int j = 0; j < 2000000; j++); // Longer delay
    }
    process_exit(0);
}

void test_process_management(void) {
    printf("Starting process management test...\n");

    int pid1 = process_create(test_process1);
    int pid2 = process_create(test_process2);

    printf("Created processes with PIDs: %d, %d\n", pid1, pid2);

    // Enable interrupts to allow scheduling
    asm volatile("sti");

    // Wait for both processes to complete
    process_wait(pid1);
    process_wait(pid2);

    printf("Process management test completed.\n");
}