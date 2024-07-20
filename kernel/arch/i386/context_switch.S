.global switch_context
switch_context:
    # Save the old context
    mov 4(%esp), %eax   # First argument: pointer to old context
    mov %ebx, 0(%eax)
    mov %ecx, 4(%eax)
    mov %edx, 8(%eax)
    mov %esi, 12(%eax)
    mov %edi, 16(%eax)
    mov %ebp, 20(%eax)
    mov (%esp), %ecx    # Save EIP
    mov %ecx, 28(%eax)
    pushf
    pop %ecx
    mov %ecx, 32(%eax)  # Save EFLAGS
    mov %cr3, %ecx
    mov %ecx, 36(%eax)  # Save CR3 (page directory base)
    mov %esp, 24(%eax)

    # Load the new context
    mov 8(%esp), %eax   # Second argument: pointer to new context
    mov 36(%eax), %ecx
    mov %ecx, %cr3      # Load new page directory base
    mov 32(%eax), %ecx
    push %ecx
    popf                # Load new EFLAGS
    mov 24(%eax), %esp  # Load new stack pointer
    push 28(%eax)       # Push new EIP to stack for ret
    mov 0(%eax), %ebx
    mov 4(%eax), %ecx
    mov 8(%eax), %edx
    mov 12(%eax), %esi
    mov 16(%eax), %edi
    mov 20(%eax), %ebp

    ret                 # Jump to new EIP