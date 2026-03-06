#include "vga.h"
#include "lib.h"

extern volatile uint16_t* vga_buffer;

static int cursor_x = 0;
static int cursor_y = 0;

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

void k_putchar(int pos, const char c, uint8_t color) {
    if (pos >= 0 && pos < (VGA_WIDTH * VGA_HEIGHT)) {
        vga_buffer[pos] = (uint16_t)c | (uint16_t)color << 8;
    }
}

void k_clear_screen() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i] = (uint16_t)' ' | (uint16_t)VGA_COLOR_WHITE << 8;
    }
    cursor_x = 0;
    cursor_y = 0;
}

void k_putchar_at_cursor(const char c, uint8_t color) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        k_putchar(cursor_y * VGA_WIDTH + cursor_x, c, color);
        cursor_x++;
    }

    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    
}

void k_putstr(const char* str, uint8_t color, int x, int y) {
    int pos = y * VGA_WIDTH + x;
    for (int i = 0; str[i] != '\0'; i++) {
        k_putchar(pos, str[i], color);  
        pos++; 
        if (pos >= (VGA_WIDTH * VGA_HEIGHT)) break;
    }
}

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