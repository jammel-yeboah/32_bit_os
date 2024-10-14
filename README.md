# 32-bit Operating System

This project is an implementation of a 32-bit operating system, focusing on core concepts and functionality. It's designed for educational purposes to understand the fundamentals of OS development.

## Key Features

- Monolithic Kernel Architecture
- Memory Management: Paging with virtual memory support
- Process Management: Completely Fair Scheduler (CFS)
- Interrupt Handling: IDT-based system for hardware and software interrupts
- System Calls: Basic implementations of fork, exec, exit, and wait
- I/O Systems: VGA text mode driver for terminal output

## Current Implementation

### Boot Process
- Multiboot-compliant bootloader
- Assembly-level initialization and protected mode switch

### Memory Management
- Two-level paging system (4KB pages)
- Physical memory management using bitmap allocation
- Basic kernel heap management (bump allocator)
- Virtual memory with 4GB address space per process

### Process Management
- Process Control Block (PCB) for process representation
- Implementation of fork, exit, and wait system calls
- Context switching mechanism
- Completely Fair Scheduler (CFS) using a red-black tree

### Scheduling
- Implemented the Completely Fair Scheduler (CFS) algorithm
- Developed a red-black tree data structure for efficient process management
- Integrated virtual runtime calculation and process selection based on CFS principles

### Interrupt Handling
- Interrupt Descriptor Table (IDT) setup
- Handlers for system calls and hardware interrupts
- Timer interrupt for preemptive multitasking (100Hz)

### I/O
- Basic VGA text mode driver for terminal output
- Simple keyboard input handling (planned)

### System Calls
- Implementation of fundamental system calls (fork, exec, exit, wait)
- System call interface using interrupt 0x80

## Building and Running

To build the OS:
1. Ensure you have a cross-compiler toolchain for i686-elf.
2. Run `make` in the project root directory.

To run the OS (using QEMU):
```
qemu-system-i386 -kernel myos.kernel
```

## Testing

The project includes basic test suites for:
- Process management
- System calls
- Memory management

Run these tests by executing the kernel and observing the output.

## Future Enhancements

1. File System: Implement a basic file system
2. User-space Memory Allocation: Develop a more sophisticated allocator
3. Inter-Process Communication (IPC): Implement basic IPC mechanisms
4. Network Stack: Add basic networking capabilities
5. Graphics: Implement a simple GUI
6. Extended Device Drivers: Support for more hardware devices

## Contributing

This is an educational project. Feel free to fork, experiment, and submit pull requests!

## Learning Resources

[OSDev.org](https://wiki.osdev.org/Main_Page) has been very helpful for this project!