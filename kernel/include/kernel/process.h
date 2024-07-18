#ifndef _KERNEL_PROCESS_H
#define _KERNEL_PROCESS_H

#include <stdint.h>

#define MAX_PROCESSES 64

typedef enum {
    PROCESS_STATE_UNUSED,
    PROCESS_STATE_READY,
    PROCESS_STATE_RUNNING,
    PROCESS_STATE_WAITING,
    PROCESS_STATE_TERMINATED
} process_state_t;

typedef struct {
    uint32_t pid;
    uint32_t parent_pid;
    process_state_t state;
    uint32_t esp;
    uint32_t ebp;
    uint32_t eip;
    int exit_status;
    // will more fields as needed (e.g., memory allocation, open files, etc.)
} process_control_block_t;

void process_init(void);
int process_create(void (*start_routine)(void));
void process_exit(int status);
int process_wait(uint32_t pid);
void process_set_current(uint32_t pid);
uint32_t process_get_current();

#endif