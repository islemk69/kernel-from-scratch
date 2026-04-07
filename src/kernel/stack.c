#include "../include/stack.h"
#include "../include/stdio.h"
#include "../include/types.h"
#include "../include/vga.h"

void print_kernel_stack(void) {
    uint32_t esp;
    uint32_t ebp;

    asm volatile("mov %%esp, %0" : "=r"(esp));
    asm volatile("mov %%ebp, %0" : "=r"(ebp));

    k_printf(VGA_COLOR_LIGHT_BLUE, "\n--- KERNEL STACK DUMP ---\n");
    k_printf(VGA_COLOR_LIGHT_CYAN, "ESP: "); k_printf(VGA_COLOR_WHITE, "0x%08x\n", esp);
    k_printf(VGA_COLOR_LIGHT_CYAN, "EBP: "); k_printf(VGA_COLOR_WHITE, "0x%08x\n", ebp);

    if (esp > ebp || (ebp - esp) > 1024) {
        k_printf(VGA_COLOR_LIGHT_RED, "Stack size seems abnormal or not in a standard frame. Aborting dump.\n");
        return;
    }

    k_printf(VGA_COLOR_YELLOW, "Address      Value\n");
    k_printf(VGA_COLOR_WHITE, "------------------------\n");

    uint32_t* ptr = (uint32_t*)esp;
    while ((uint32_t)ptr <= ebp) {
        k_printf(VGA_COLOR_LIGHT_CYAN, "0x%08x"); k_printf(VGA_COLOR_WHITE, " : 0x%08x\n", (uint32_t)ptr, *ptr);
        ptr++;
    }

    k_printf(VGA_COLOR_WHITE, "------------------------\n");
}
