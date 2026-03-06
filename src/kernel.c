#include "include/types.h"
#include "include/vga.h"
#include "include/lib.h"
#include "include/stdio.h"
#include "include/keyboard.h"

volatile uint16_t* vga_buffer = (uint16_t*)VGA_ADDRESS;

void init_kernel(void) {
    k_clear_screen();
}

void k_test_features(void) {
    k_printf("KFS-1: Kernel initialized successfully!\n");
    k_printf("---------------------------------------\n");
    k_printf("Testing Scroll Bonus...\n");
    
    for (int i = 0; i < 30; i++) {
        k_printf("Ceci est la ligne numero : %d\n", i);
    }

    k_printf("\nIf you see this message, scroll is working !\n");
    k_printf("Keyboard is active. Type something:\n> ");
}

void kmain(void) {
    init_kernel();
    k_test_features();
    
    while (42) {
        k_handle_keyboard();
    };
}