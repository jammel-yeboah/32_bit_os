.global syscall_handler_asm

syscall_handler_asm:
    pushl %eax
    pushl %ecx
    pushl %edx
    call syscall_handler_c
    addl $4, %esp  # Remove syscall number from stack
    popl %edx
    popl %ecx
    popl %eax
    iret