#ifndef _KEYBOARD_DRIVER_H
#define _KEYBOARD_DRIVER_H

#include <stddef.h>
#include <stdint.h>

typedef uint8_t key_t;

static const char
    keyboard[128] =
        {
            0,    27,  '1', '2', '3',  '4',  '5', '6', '7',  '8',
            '9',  '0', '-', '=', '\b', '\t', 'q', 'w', 'e',  'r',
            't',  'y', 'u', 'i', 'o',  'p',  '[', ']', '\n', 0, /* Ctrl */
            'a',  's', 'd', 'f', 'g',  'h',  'j', 'k', 'l',  ';',
            '\'', '`', 0, /* Left Shift */
            '\\', 'z', 'x', 'c', 'v',  'b',  'n', 'm', ',',  '.',
            '/',  0, /* Right Shift */
            '*',  0, /* Alt */
            ' ',     /* Space */
            0,       /* Caps Lock */
            0,    0,   0,   0,   0,    0,    0,   0,   0,    0, /* F1-F10 */
            0,                                                  /* Num Lock */
            0,                            /* Scroll Lock */
            0,    0,   0,   '-',          /* Home, Up, PgUp, Numpad - */
            0,    0,   0,   '+',          /* Left, Down, Right, Numpad + */
            0,    0,   0,   0,   0,    0, /* End, PgDn, Ins, Del */
            0,    0,   0,   0,   0,    0,    0,   0, /* F11, F12, ... */
};

char keyboard_getc(void);

char *keyboard_getl(char *str, size_t n);

typedef void (*keyboard_on_char)(char c);
char *keyboard_getl_fnptr(char *str, size_t n, keyboard_on_char fn);

#endif // _KEYBOARD_DRIVER_H
