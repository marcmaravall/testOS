.globl   isr_wrapper
.align   4

isr_wrapper:
    pusha
    cld
    call interrupt_handler
    popa
    iret
