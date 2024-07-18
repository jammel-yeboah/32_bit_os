# 32-bit Operating System

This project is a basic implementation of a 32-bit operating system, focusing on core concepts and functionality. It's designed for personal educational purposes to understand the fundamentals of OS development.

## Key Features

- Process Management: Process Control Block (PCB) structure and basic lifecycle management
- Interrupt Handling: Interrupt Descriptor Table (IDT) and system call interface
- Memory Management: Simple memory allocation for processes
- I/O Systems: Basic terminal driver for output
- System Calls: fork, exit, wait, exec
- Custom Executable Format: For loading and executing user programs

## Current Implementation

### Process Management
- Implemented a comprehensive Process Control Block (PCB) structure
- Created a process table to manage multiple processes
- Developed system calls (fork, exit, wait, exec) to handle the process lifecycle

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

## Planned Additions

1. Enhanced Interrupt Handling
   - Implement handlers for hardware interrupts and exceptions

2. Context Switching
   - Develop a full mechanism to switch between processes

3. CPU Scheduling
   - Implement basic scheduling algorithms (e.g., Round Robin)

4. Memory Management
   - Implement dynamic memory allocation for processes

5. File System
   - Develop a simple file system for program storage and execution

6. User Mode
   - Implement separation between kernel and user mode

## Building and Running

(Instructions for building and running the OS will be added here once the build process is finalized)

## Contributing

This is an educational project. Feel free to fork and experiment!

## Learning Resources

For more information on OS development, visit [OSDev.org](https://wiki.osdev.org/Main_Page).
