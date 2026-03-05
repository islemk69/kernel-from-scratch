#include "../include/vga.h"

// void k_clean_screen() {

// }

extern volatile uint16_t* vga_buffer;

void k_putchar(int pos, const char c, uint8_t color) {
    if (pos >= 0 && pos < (VGA_WIDTH * VGA_HEIGHT)) {
        vga_buffer[pos] = (uint16_t)c | (uint16_t)color << 8;
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