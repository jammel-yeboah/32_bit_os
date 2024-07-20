#include <kernel/process.h>
#include <kernel/tty.h>
#include <kernel/timer.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

process_control_block_t processes[MAX_PROCESSES];
static uint32_t next_pid = 1;
static uint32_t current_pid = 0;

extern void switch_to_user_mode(void);
extern void switch_context(context_t* old, context_t* new);

void process_init(void) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        processes[i].state = PROCESS_STATE_UNUSED;
        processes[i].total_runtime = 0;
        processes[i].vruntime = 0;
        processes[i].nice = 0;
    }
    printf("Process management initialized.\n");
}

int process_create(void (*start_routine)(void)) {
    int i;
    for (i = 0; i < MAX_PROCESSES; i++) {
        if (processes[i].state == PROCESS_STATE_UNUSED) {
            break;
        }
    }
    
    if (i == MAX_PROCESSES) {
        return -1;  // No free PCB
    }

    processes[i].pid = next_pid++;
    processes[i].parent_pid = current_pid;
    processes[i].state = PROCESS_STATE_READY;
    processes[i].total_runtime = 0;
    processes[i].start_time = timer_get_ticks();
    processes[i].vruntime = 0;
    processes[i].nice = 0;

    // Set up the initial context
    memset(&processes[i].context, 0, sizeof(context_t));
    processes[i].context.eip = (uint32_t)start_routine;
    processes[i].context.eflags = 0x202; // Interrupt enabled
    processes[i].kernel_stack = (uint32_t)malloc(4096) + 4096; // Allocate 4KB for kernel stack
    processes[i].context.esp = processes[i].kernel_stack;

    return processes[i].pid;
}

void process_exit(int status) {
    printf("Process %d exited with status %d\n", current_pid, status);
    processes[current_pid].state = PROCESS_STATE_TERMINATED;

    // Update runtime before terminating
    process_update_runtime(current_pid);

    // Wake up parent if it's waiting
    if (processes[processes[current_pid].parent_pid].state == PROCESS_STATE_WAITING) {
        processes[processes[current_pid].parent_pid].state = PROCESS_STATE_READY;
    }

    // TODO: Implement proper scheduling here
    // For now, we'll just halt
    while(1);
}

int process_wait(uint32_t pid) {
    int i;
    for (i = 0; i < MAX_PROCESSES; i++) {
        if (processes[i].pid == pid) {
            break;
        }
    }

    if (i == MAX_PROCESSES) {
        return -1;  // Process not found
    }

    if (processes[i].state == PROCESS_STATE_TERMINATED) {
        int status = processes[i].exit_status;
        processes[i].state = PROCESS_STATE_UNUSED;  // Clean up the process
        return status;
    }

    // If the process is still running, wait for it
    processes[current_pid].state = PROCESS_STATE_WAITING;
    // TODO: Implement proper scheduling here
    // For now, we'll just spin
    while (processes[i].state != PROCESS_STATE_TERMINATED);

    int status = processes[i].exit_status;
    processes[i].state = PROCESS_STATE_UNUSED;  // Clean up the process
    return status;
}

void process_set_current(uint32_t pid) {
    if (current_pid != 0) {
        process_update_runtime(current_pid);
    }
    current_pid = pid;
    processes[pid].start_time = timer_get_ticks();
}

uint32_t process_get_current(void) {
    return current_pid;
}

void process_switch(uint32_t new_pid) {
    if (current_pid == new_pid) {
        return; // No need to switch
    }

    uint32_t old_pid = current_pid;
    process_update_runtime(old_pid);
    process_set_current(new_pid);

    processes[old_pid].state = PROCESS_STATE_READY;
    processes[new_pid].state = PROCESS_STATE_RUNNING;

    switch_context(&processes[old_pid].context, &processes[new_pid].context);
}

void process_update_runtime(uint32_t pid) {
    uint64_t current_time = timer_get_ticks();
    uint64_t runtime = current_time - processes[pid].start_time;
    processes[pid].total_runtime += runtime;
    
    // Update vruntime (simplified version, we'll refine this for CFS later)
    processes[pid].vruntime += runtime * (1 + processes[pid].nice * 0.1);
}