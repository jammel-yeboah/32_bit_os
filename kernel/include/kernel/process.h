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
    uint32_t eax, ebx, ecx, edx;
    uint32_t esi, edi, ebp, esp;
    uint32_t eip;
    uint32_t eflags;
    uint32_t cr3; // Page directory base
} context_t;

typedef struct {
    uint32_t pid;
    uint32_t parent_pid;
    process_state_t state;
    context_t context;
    uint32_t kernel_stack;
    uint64_t total_runtime;    // Total runtime in nanoseconds
    uint64_t start_time;       // Time when the process started/resumed running
    uint64_t vruntime;         // Virtual runtime for CFS
    int nice;                  // Nice value for CFS (-20 to +19)
    // will add more fields as needed (e.g., memory allocation, open files, etc.)
} process_control_block_t;

void process_init(void);
int process_create(void (*start_routine)(void));
void process_exit(int status);
int process_wait(uint32_t pid);
void process_set_current(uint32_t pid);
uint32_t process_get_current(void);
void process_switch(uint32_t pid);
void process_update_runtime(uint32_t pid);

extern process_control_block_t processes[MAX_PROCESSES];

#endif