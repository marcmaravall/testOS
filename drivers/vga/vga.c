#include "vga.h"
#include <lib/string.h>

size_t vga_terminal_row;
size_t vga_terminal_column;
uint8_t vga_terminal_color;

int vga_terminal_init() {
  vga_terminal_column = 0;
  vga_terminal_row = 0;
  vga_terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      vga_terminal_buffer[index] = vga_entry(' ', vga_terminal_color);
    }
  }
  return 0;
}

void vga_terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  vga_terminal_buffer[index] = vga_entry(c, color);
}

int vga_terminal_putchar(const char c) {
  if (c == '\n') {
    if (++vga_terminal_row >= VGA_HEIGHT)
      vga_terminal_row = 0;
    vga_terminal_column = 0;
    return 0;
  }
  vga_terminal_putentryat(c, vga_terminal_color, vga_terminal_column,
                          vga_terminal_row);
  if (++vga_terminal_column == VGA_WIDTH) {
    vga_terminal_column = 0;
    if (++vga_terminal_row == VGA_HEIGHT)
      vga_terminal_row = 0;
  }
  return 0;
}

int vga_terminal_print(const char *str) {
  size_t size = strlen(str);
  return vga_terminal_write(str, size);
}

int vga_terminal_write(const char *str, size_t len) {
  for (size_t i = 0; i < len; i++)
    vga_terminal_putchar(str[i]);
  return 0;
}
