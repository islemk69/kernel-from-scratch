#include "include/types.h"
#include "include/vga.h"
#include "include/stdio.h"
#include "include/gdt.h"
#include "include/shell.h"
#include "include/boot_display.h"

volatile uint16_t* vga_buffer = (uint16_t*)VGA_ADDRESS;

void init_kernel(void) {
    vga_init_screens();
}

void kmain(void) {
    init_gdt();
    init_kernel();
    k_test_features();
    k_shell();
}