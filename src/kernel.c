#include "include/types.h"
#include "include/vga.h"
#include "include/lib.h"
#include "include/stdio.h"
#include "include/keyboard.h"

volatile uint16_t* vga_buffer = (uint16_t*)VGA_ADDRESS;

void init_kernel(void) {
    vga_init_screens();
}

void k_test_features(void) {
    k_printf("KFS-1: Kernel initialized successfully!\n");
    k_printf("You are currently on Screen 0 !!\n\n");
    
    k_printf("MULTIPLE SCREENS BONUS:\n");
    k_printf("- Press F1 to view Terminal 0\n");
    k_printf("- Press F2 to view Terminal 1\n");
    k_printf("- Press F3 to view Terminal 2\n");
    k_printf("- Press F4 to view Terminal 3\n\n");

    k_printf("Keyboard is active. Type something: (it's a real prompt... or not.)\n> ");
}

void kmain(void) {
    init_kernel();
    k_test_features();
    
    while (42) {
        k_handle_keyboard();
    };
}