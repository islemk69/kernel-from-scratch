#include "include/types.h"
#include "include/vga.h"
#include "include/lib.h"

volatile uint16_t* vga_buffer = (uint16_t*)VGA_ADDRESS;

void kmain(void) {
    k_clear_screen();

    k_printf("KFS-1: Kernel 42 booting...\n");
    k_printf("---------------------------\n");

    k_printf("[OK] VGA Interface initialized at %x\n", VGA_ADDRESS);
    k_printf("[OK] Screen resolution: %d x %d\n", VGA_WIDTH, VGA_HEIGHT);
    
    k_putstr("System Loaded", VGA_COLOR_LIGHT_GREEN, 32, 24);

    while (1);
}