#include "keyboard.h"
#include "io.h"
#include "vga.h"

unsigned char kbd_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	
  '9', '0', '-', '=', '\b',	
  '\t',			
  'q', 'w', 'e', 'r',
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	
    0,
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
 '\'', '`',   0,
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',
  'm', ',', '.', '/',   0,
  '*',
    0,
  ' ',
    0,
};

void k_handle_keyboard() {
    if (inb(0x64) & 1) {
        uint8_t scancode = inb(0x60);

        if (!(scancode & 0x80)) {
            char c = kbd_map[scancode];
            if (c != 0) {
                k_putchar_at_cursor(c, VGA_COLOR_WHITE);
            }
        }
    }
}
