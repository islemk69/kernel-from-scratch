#include "stdio.h"
#include "vga.h"
#include "string.h"

void k_printf(uint8_t color, const char *format, ...) {
    va_list args;
    va_start(args, format);

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;
            int pad = 0;
            char pad_char = ' ';
            if (format[i] == '0') {
                pad_char = '0';
                i++;
            }
            while (format[i] >= '0' && format[i] <= '9') {
                pad = pad * 10 + (format[i] - '0');
                i++;
            }

            if (format[i] == 's') {
                char *s = va_arg(args, char *);
                while (*s) k_putchar_at_cursor(*s++, color);
            } else if (format[i] == 'd') {
                int d = va_arg(args, int);
                char buf[32];
                k_itoa(d, buf, 10);
                int len = k_strlen(buf);
                for (int p = 0; p < pad - len; p++) {
                    k_putchar_at_cursor(pad_char, color);
                }
                char *p = buf;
                while (*p) k_putchar_at_cursor(*p++, color);
            } else if (format[i] == 'x' || format[i] == 'X') {
                uint32_t x = va_arg(args, uint32_t);
                char *digits = (format[i] == 'X') ? "0123456789ABCDEF" : "0123456789abcdef";
                char buf[9];
                buf[8] = '\0';
                for (int j = 7; j >= 0; j--) {
                    buf[j] = digits[x & 0xF];
                    x >>= 4;
                }
                char *p = buf;
                if (pad == 0) {
                    while (*p == '0' && *(p+1) != '\0') p++;
                }
                int len = k_strlen(p);
                for (int p_count = 0; p_count < pad - len; p_count++) {
                    k_putchar_at_cursor(pad_char, color);
                }
                while (*p) k_putchar_at_cursor(*p++, color);
            } else if (format[i] == '%') {
                k_putchar_at_cursor('%', color);
            }
        } else {
            k_putchar_at_cursor(format[i], color);
        }
    }
    va_end(args);
}
