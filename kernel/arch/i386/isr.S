.extern isr_handler
.extern irq_handler

# Common ISR code
isr_common_stub:
    pusha
    push %ds
    push %es
    push %fs
    push %gs
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %esp, %eax
    push %eax
    mov $isr_handler, %eax
    call *%eax
    pop %eax
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $8, %esp
    iret

# Common IRQ code
irq_common_stub:
    pusha
    push %ds
    push %es
    push %fs
    push %gs
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %esp, %eax
    push %eax
    mov $irq_handler, %eax
    call *%eax
    pop %eax
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $8, %esp
    iret

# ISR handlers
.global isr0
.global isr1
# ... (define more ISRs)
.global isr31

# IRQ handlers
.global irq0
.global irq1
# ... (define more IRQs)
.global irq15

# ISR and IRQ handler implementations
isr0:
    push $0
    push $0
    jmp isr_common_stub

isr1:
    push $0
    push $1
    jmp isr_common_stub

# ... (implement more ISRs)

irq0:
    push $0
    push $32
    jmp irq_common_stub

irq1:
    push $0
    push $33
    jmp irq_common_stub

# ... (implement more IRQs)