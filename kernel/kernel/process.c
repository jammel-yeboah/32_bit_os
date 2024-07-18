#include <kernel/process.h>
#include <kernel/tty.h>
#include <stdio.h>
#include <string.h>

static process_control_block_t processes[MAX_PROCESSES];
static uint32_t next_pid = 1;
static uint32_t current_pid = 0;

void process_init(void) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        processes[i].state = PROCESS_STATE_UNUSED;
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
    processes[i].state = PROCESS_STATE_READY;
    processes[i].parent_pid = current_pid;
    
    if (start_routine == NULL && current_pid != 0) {
        // This is a fork, so copy the parent's context
        memcpy(&processes[i], &processes[current_pid], sizeof(process_control_block_t));
        processes[i].pid = next_pid - 1;  // Assign the new PID
        processes[i].parent_pid = current_pid;
    } else {
        // TODO: Set up stack and other necessary initializations
        processes[i].esp = 0;  // This should be set to a proper stack pointer
        processes[i].ebp = 0;  // This should be set to a proper base pointer
    }

    return processes[i].pid;
}

void process_exit(int status) {
    printf("Process %d exited with status %d\n", current_pid, status);
    processes[current_pid].state = PROCESS_STATE_TERMINATED;
    processes[current_pid].exit_status = status;

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
    current_pid = pid;
}

uint32_t process_get_current() {
    return current_pid;
}