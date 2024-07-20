#include <kernel/timer.h>
#include <kernel/idt.h>
#include <kernel/process.h>
#include <stdio.h>

#define CLOCK_TICK_RATE 1193180
#define TICKS_PER_SECOND 100

volatile uint64_t ticks = 0;

void timer_handler(struct regs *r) {
    ticks++;
    if (ticks % TICKS_PER_SECOND == 0) {
        printf("Tick: %llu\n", ticks);
    }

    // Update runtime for the current process
    process_update_runtime(process_get_current());

    // Simple round-robin scheduling
    uint32_t current = process_get_current();
    uint32_t next = (current + 1) % MAX_PROCESSES;
    while (next != current) {
        if (processes[next].state == PROCESS_STATE_READY) {
            process_switch(next);
            break;
        }
        next = (next + 1) % MAX_PROCESSES;
    }
}

void timer_install() {
    // Set the interrupt handler
    irq_install_handler(0, timer_handler);

    // Get the PIT value: hardware clock at 1193180 Hz
    uint32_t divisor = CLOCK_TICK_RATE / TICKS_PER_SECOND;

    // Send the command byte
    outb(0x43, 0x36);

    // Send the frequency divisor
    outb(0x40, (uint8_t)(divisor & 0xFF));
    outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));

    printf("Timer installed.\n");
}

uint64_t timer_get_ticks() {
    return ticks;
}

uint64_t timer_get_time_ns() {
    return (ticks * 1000000000) / TICKS_PER_SECOND;
}