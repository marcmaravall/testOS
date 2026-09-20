.section .bss
.align 8
idt: .skip 256*8
idt_end:

.section .data
.align 4
idtr:
    .word idt_end-idt-1  
    .long idt                

.section .text
.globl idt_init
.globl idt_set_gate

idt_init:
    movl $isr_wrapper, %eax
    movl $0x10, %ecx
    call idt_set_gate

    lidt idtr
    ret

idt_set_gate:
    leal idt(,%ecx,8), %edx
    movw %ax, 0(%edx)
    movw %cs, 2(%edx)
    movb $0, 4(%edx)
    movb $0x8E, 5(%edx)
    shrl $16, %eax
    movw %ax, 6(%edx)
    ret
