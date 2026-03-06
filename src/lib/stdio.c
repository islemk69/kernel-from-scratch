#include "stdio.h"
#include "vga.h"
#include "lib.h"

void k_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;
            if (format[i] == 's') {
                char *s = va_arg(args, char *);
                while (*s) k_putchar_at_cursor(*s++, VGA_COLOR_WHITE);
            } else if (format[i] == 'd') {
                int d = va_arg(args, int);
                char buf[32];
                k_itoa(d, buf, 10);
                char *p = buf;
                while (*p) k_putchar_at_cursor(*p++, VGA_COLOR_WHITE);
            } else if (format[i] == 'x') {
                int x = va_arg(args, int);
                char buf[32];
                k_itoa(x, buf, 16);
                k_putchar_at_cursor('0', VGA_COLOR_WHITE);
                k_putchar_at_cursor('x', VGA_COLOR_WHITE);
                char *p = buf;
                while (*p) k_putchar_at_cursor(*p++, VGA_COLOR_WHITE);
            }
        } else {
            k_putchar_at_cursor(format[i], VGA_COLOR_WHITE);
        }
    }
    va_end(args);
}
