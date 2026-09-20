#include "keyboard.h"
#include <lib/stdio.h>

char keyboard_scancode_to_ascii(uint8_t scancode) {
  if (scancode > 127)
    return 0;
  return keyboard[scancode];
}

char keyboard_getc(void) {
  uint8_t scancode;
  while (!(inb(0x64) & 0x01)) {
  }
  scancode = inb(0x60);

  return keyboard_scancode_to_ascii(scancode);
}
