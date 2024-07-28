# 32-bit Operating System

This project is a basic implementation of a 32-bit operating system, focusing on core concepts and functionality. It's designed for personal educational purposes to understand the fundamentals of OS development.

## Key Features

- Process Management: Process Control Block (PCB) structure and advanced lifecycle management
- Interrupt Handling: Interrupt Descriptor Table (IDT) and system call interface
- Memory Management: Simple memory allocation for processes
- I/O Systems: Basic terminal driver for output
- System Calls: fork, exit, wait, exec
- Custom Executable Format: For loading and executing user programs
- Completely Fair Scheduler (CFS): Advanced process scheduling

## Current Implementation

### Process Management
- Implemented a comprehensive Process Control Block (PCB) structure
- Created a process table to manage multiple processes
- Developed system calls (fork, exit, wait, exec) to handle the process lifecycle
- Implemented context switching mechanism for process execution

### Interrupt Handling
- Set up the Interrupt Descriptor Table (IDT) to manage various interrupt types
- Implemented an assembly-level interrupt handler with C-level dispatch
- Created a system call handler to process user requests

### Memory Management
- Implemented basic memory allocation for processes
- Developed a simple memory copying mechanism for the fork system call

### I/O
- Implemented a basic terminal driver for text output
- Integrated printf-style formatting for debugging and user interaction

### Executable Loading
- Designed a simple executable format to demonstrate program loading and execution
- Implemented the exec system call to load and run programs

### Scheduling
- Implemented the Completely Fair Scheduler (CFS) algorithm
- Developed a red-black tree data structure for efficient process management
- Integrated virtual runtime calculation and process selection based on CFS principles

### Testing
- Added a test suite for process management and system calls
- Implemented test processes to verify scheduler functionality

## Planned Additions

1. Enhanced Memory Management
   - Implement paging or segmentation for more efficient memory use
   - Develop dynamic memory allocation for processes

2. File System
   - Design and implement a simple file system for persistent storage

3. User Mode
   - Implement proper separation between kernel and user mode
   - Add memory protection mechanisms

4. Inter-Process Communication (IPC)
   - Develop basic IPC mechanisms like pipes or message queues

5. Device Drivers
   - Implement basic device drivers (e.g., keyboard, display)

## Building and Running

To build the OS:
1. Ensure you have the necessary cross-compiler toolchain installed.
2. Run `make` in the project root directory.

To run the OS (assuming you're using QEMU):
```
qemu-system-i386 -kernel myos.kernel
```

## Testing

The project includes a test suite to verify the functionality of various components:

1. Process Management Tests: Located in `tests/process/process_test.c`
2. System Call Tests: Located in `tests/syscall/syscall_test.c`

These tests are automatically compiled and linked with the kernel. The test results will be displayed during kernel execution.

## Contributing

This is an educational project. Feel free to fork and experiment!

## Learning Resources

For more information on OS development, visit [OSDev.org](https://wiki.osdev.org/Main_Page).