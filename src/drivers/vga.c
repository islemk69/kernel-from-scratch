#include "vga.h"
#include "lib.h"
#include "io.h"

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

void update_hardware_cursor(int x, int y) {
    uint16_t pos = y * VGA_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void k_scroll() {
    for (int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++) {
        vga_buffer[i] = vga_buffer[i + VGA_WIDTH];
    }

    for (int i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < VGA_HEIGHT * VGA_WIDTH; i++) {
        vga_buffer[i] = (uint16_t)' ' | (uint16_t)VGA_COLOR_WHITE << 8;
    }
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

    if (cursor_y >= VGA_HEIGHT) {
        k_scroll();
        cursor_y = VGA_HEIGHT - 1; 
    }

    update_hardware_cursor(cursor_x, cursor_y);
}

void k_putstr(const char* str, uint8_t color, int x, int y) {
    int pos = y * VGA_WIDTH + x;
    for (int i = 0; str[i] != '\0'; i++) {
        k_putchar(pos, str[i], color);  
        pos++; 
        if (pos >= (VGA_WIDTH * VGA_HEIGHT)) break;
    }
}