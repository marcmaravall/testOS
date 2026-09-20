#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>

// size long enough to contain any possible value
#define IOTA_STR_SIZE (8 * sizeof(int) + 1)

char *iota(int num, char *str, size_t size, int base);

#endif // STDLIB_H
