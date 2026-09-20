#include "stdlib.h"
#include "string.h"

char *iota(int num, char *str, size_t size, int base) {
  static char digits[32] = {'0', '1', '2', '3', '4', '5', '6', '7',
                            '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
                            'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
                            'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V'};

  if (base < 2 || size == 0)
    return str;
  str[size - 1] = '\0';
  size_t i = size - 1;
  while (num && i > 0) {
    int dig = num % base;
    str[--i] = digits[dig];
    num /= base;
  }
  return &str[i];
}
