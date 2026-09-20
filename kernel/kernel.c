#include <drivers/keyboard/keyboard.h>
#include <drivers/vga/vga.h>
#include <lib/stdlib.h>
#include <lib/string.h>

#if defined(__linux__)
#error                                                                         \
    "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
#if !defined(__i386__)
#error "This os needs to be compiled with a ix86-elf compiler"
#endif

extern void idt_init(void);
extern void isr(void);

void kernel_main(void) {
  idt_init();
  vga_terminal_init();
  __asm__ volatile("int $0x21");
  vga_terminal_print("Hello, world\n");
  while (1) {
    vga_terminal_setcolor_at(vga_terminal_column, vga_terminal_row,
                             vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_WHITE));
    char key = keyboard_getc();
    if (key == 0x00)
      continue;
    vga_terminal_putchar(key);
  }
}

void example(void) { vga_terminal_print("Interrupt 0x21\n"); }

void interrupt_handler(void) { vga_terminal_print("Received interrupt\n"); }
