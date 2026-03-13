#include "../include/shell.h"
#include "../include/keyboard.h"
#include "../include/stdio.h"
#include "../include/string.h"
#include "../include/stack.h"
#include "../include/io.h"
#include "../include/vga.h"

extern char k_getchar(void);

#define CMD_BUFFER_SIZE 256
char cmd_buffer[CMD_BUFFER_SIZE];
int cmd_index = 0;

void shell_execute(char* cmd) {
    if (k_strcmp(cmd, "") == 0) {
        return;
    } else if (k_strcmp(cmd, "help") == 0) {
        k_printf(VGA_COLOR_LIGHT_MAGENTA, "Available commands:\n");
        k_printf(VGA_COLOR_LIGHT_CYAN, "  help   "); k_printf(VGA_COLOR_WHITE, "- Show this help message\n");
        k_printf(VGA_COLOR_LIGHT_CYAN, "  stack  "); k_printf(VGA_COLOR_WHITE, "- Dump the kernel stack\n");
        k_printf(VGA_COLOR_LIGHT_CYAN, "  clear  "); k_printf(VGA_COLOR_WHITE, "- Clear current TTY\n");
        k_printf(VGA_COLOR_LIGHT_CYAN, "  halt   "); k_printf(VGA_COLOR_WHITE, "- Halt the CPU\n");
        k_printf(VGA_COLOR_LIGHT_CYAN, "  reboot "); k_printf(VGA_COLOR_WHITE, "- Reboot the system\n");
        k_printf(VGA_COLOR_LIGHT_MAGENTA, "Keyboard shortcuts:\n");
        k_printf(VGA_COLOR_LIGHT_CYAN, "  F1-F4  "); k_printf(VGA_COLOR_WHITE, "- Switch between virtual terminals 0-3\n");
    } else if (k_strcmp(cmd, "stack") == 0) {
        print_kernel_stack();
    } else if (k_strcmp(cmd, "clear") == 0) {
        k_clear_screen();
    } else if (k_strcmp(cmd, "halt") == 0) {
        k_printf(VGA_COLOR_LIGHT_RED, "Halting the system...\n");
        asm volatile("cli");
        asm volatile("hlt");
    } else if (k_strcmp(cmd, "reboot") == 0) {
        k_printf(VGA_COLOR_YELLOW, "Rebooting...\n");
        uint8_t good = 0x02;
        while (good & 0x02) {
            good = inb(0x64);
        }
        outb(0x64, 0xFE);
        asm volatile("cli");
        asm volatile("hlt");
    } else {
        k_printf(VGA_COLOR_LIGHT_RED, "Unknown command: %s\n", cmd);
    }
}

void k_shell(void) {
    // Prompt in every screen
    for (int s = 1; s < 4; s++) {
        vga_switch_screen(s);
        k_printf(VGA_COLOR_LIGHT_MAGENTA, "kfs>");
    }
    vga_switch_screen(0);
    k_printf(VGA_COLOR_LIGHT_MAGENTA, "kfs>");
    k_memset(cmd_buffer, 0, CMD_BUFFER_SIZE);

    while (1) {
        if (inb(0x64) & 1) {
            uint8_t scancode = inb(0x60);

            // RELEASE
            if (scancode & 0x80) {
                continue;
            }

            // F1-F4
            if (scancode >= 0x3B && scancode <= 0x3E) {
                int screen_id = scancode - 0x3B;
                vga_switch_screen(screen_id);
                continue;
            }

            extern unsigned char kbd_map[128];
            char c = kbd_map[scancode];

            if (c == 0) continue;

            if (c == '\n') {
                k_putchar_at_cursor('\n', VGA_COLOR_WHITE);
                cmd_buffer[cmd_index] = '\0';
                shell_execute(cmd_buffer);

                cmd_index = 0;
                k_memset(cmd_buffer, 0, CMD_BUFFER_SIZE);
                k_printf(VGA_COLOR_LIGHT_MAGENTA, "kfs>");
            } else if (c == '\b') {
                if (cmd_index > 0) {
                    cmd_index--;
                    cmd_buffer[cmd_index] = 0;
                    k_putchar_at_cursor('\b', VGA_COLOR_WHITE);
                    k_putchar_at_cursor(' ', VGA_COLOR_WHITE);
                    k_putchar_at_cursor('\b', VGA_COLOR_WHITE);
                }
            } else if (cmd_index < CMD_BUFFER_SIZE - 1) {
                cmd_buffer[cmd_index++] = c;
                k_putchar_at_cursor(c, VGA_COLOR_WHITE);
            }
        }
    }
}
