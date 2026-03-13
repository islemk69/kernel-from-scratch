#include "../include/boot_display.h"
#include "../include/vga.h"
#include "../include/stdio.h"

void fake_loading(void) {
    int bar_width = 20;

    #define LOAD(label, color, delay) \
        k_printf(VGA_COLOR_YELLOW, label); \
        for (int i = 0; i < bar_width; i++) { \
            for (volatile int d = 0; d < (delay); d++); \
            k_printf((color), "."); \
        } \
        k_printf(VGA_COLOR_LIGHT_GREEN, " OK!\n");

    LOAD("Booting kernel                              ", VGA_COLOR_LIGHT_GREEN,  8000000)
    LOAD("Calculating 42                              ", VGA_COLOR_LIGHT_CYAN,   5000000)
    LOAD("Negotiating with CPU                        ", VGA_COLOR_LIGHT_BLUE,   7000000)
    LOAD("Installing quantum entanglement layer       ", VGA_COLOR_LIGHT_MAGENTA,6000000)
    LOAD("Asking ChatGPT for kernel advice            ", VGA_COLOR_LIGHT_RED,    9000000)
    LOAD("Ignoring ChatGPT advice                     ", VGA_COLOR_YELLOW,       4000000)
    LOAD("Overclocking RAM to 999MHz                  ", VGA_COLOR_LIGHT_CYAN,   7000000)
    LOAD("Loading GDT (for real this time)            ", VGA_COLOR_LIGHT_GREEN,  5000000)
    LOAD("Bribing the scheduler                       ", VGA_COLOR_LIGHT_BLUE,   6000000)
    LOAD("Pretending to load drivers                  ", VGA_COLOR_LIGHT_MAGENTA,8000000)
    LOAD("Compiling kernel in prod (yes really)       ", VGA_COLOR_LIGHT_RED,    9000000)
    LOAD("Reversing the polarity of the neutron flow  ", VGA_COLOR_LIGHT_CYAN,   7000000)
    LOAD("Resolving DNS (we have no network stack)    ", VGA_COLOR_YELLOW,       5000000)
    LOAD("Asking user to restart if this fails        ", VGA_COLOR_LIGHT_GREEN,  6000000)
    LOAD("This step does literally nothing            ", VGA_COLOR_LIGHT_BLUE,   4000000)
    LOAD("Faking the moon landing                     ", VGA_COLOR_LIGHT_MAGENTA,7000000)
    LOAD("Loading shell (finally)                     ", VGA_COLOR_LIGHT_GREEN,  8000000)
    k_printf(VGA_COLOR_LIGHT_GREEN, "\nAll systems nominal. Probably.\n\n");
}

void k_test_features(void) {
    fake_loading();
    k_printf(VGA_COLOR_LIGHT_GREEN, "KFS: Kernel initialized successfully!\n");
    k_printf(VGA_COLOR_YELLOW, "Welcome to my OS! (Yeah, i know, we're still in the boot...)\n");
    k_printf(VGA_COLOR_LIGHT_CYAN, "Type 'help' to see available commands and keyboard shortcuts.\n\n");
}
