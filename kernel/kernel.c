#include <drivers/vga/vga.h>
#include <lib/stdlib.h>
#include <lib/string.h>

extern void idt_init(void);
extern void isr(void);

#if defined(__linux__)
#error                                                                         \
    "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
#if !defined(__i386__)
#error "This os needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) {
  idt_init();
  vga_terminal_init();
  __asm__ volatile("int $0x10");
  char c[10];
  char *s = iota(255, c, sizeof(c), 8);
  vga_terminal_print("Hello, world\n");
  vga_terminal_write(s, strlen(s));
}

void interrupt_handler(void) { vga_terminal_print("Received interrupt\n"); }
