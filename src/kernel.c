#include "include/types.h"
#include "include/vga.h"
#include "include/lib.h"

volatile uint16_t* vga_buffer = (uint16_t*)VGA_ADDRESS;

void kmain(void) {
    for (int i = 0; i < 80 * 25; i++) vga_buffer[i] = 0x0F20;

    k_putstr("bonjour", VGA_COLOR_LIGHT_GREEN, 10, 5);
    k_putstr("Kernel Loaded", VGA_COLOR_LIGHT_GREEN, 32, 10);
    k_putstr("42", VGA_COLOR_YELLOW, 39, 12);

    while (1);
}