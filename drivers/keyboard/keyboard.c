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

char *keyboard_getl_fnptr(char *str, size_t n, keyboard_on_char fn) {
  char c = keyboard_getc();
  if (fn)
    fn(c);
  size_t i = 0;
  for (i; c != '\n' && i < n - 1; i++) {
    if (c != 0) {
      str[i] = c;
    } else {
      i--;
    }
    c = keyboard_getc();
    if (fn)
      fn(c);
  }
  str[i] = '\0';
  return str;
}

char *keyboard_getl(char *str, size_t n) {
  return keyboard_getl_fnptr(str, n, NULL);
}
