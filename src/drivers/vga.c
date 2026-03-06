#include "vga.h"
#include "lib.h"
#include "io.h"

extern volatile uint16_t* vga_buffer;

typedef struct {
    uint16_t buffer[VGA_WIDTH * VGA_HEIGHT];
    int cursor_x;
    int cursor_y;
} screen_state_t;

static screen_state_t screens[NUM_SCREENS];
static int current_screen = 0;

static int cursor_x = 0;
static int cursor_y = 0;

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

void k_putchar(int pos, const char c, uint8_t color) {
    if (pos >= 0 && pos < (VGA_WIDTH * VGA_HEIGHT)) {
        uint16_t entry = (uint16_t)c | (uint16_t)color << 8;
        screens[current_screen].buffer[pos] = entry;
        vga_buffer[pos] = entry;
    }
}

void k_clear_screen() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        uint16_t entry = (uint16_t)' ' | (uint16_t)VGA_COLOR_WHITE << 8;
        screens[current_screen].buffer[i] = entry;
        vga_buffer[i] = entry;
    }
    cursor_x = 0;
    cursor_y = 0;
    screens[current_screen].cursor_x = 0;
    screens[current_screen].cursor_y = 0;
}

void update_hardware_cursor(int x, int y) {
    uint16_t pos = y * VGA_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void k_scroll() {
    for (int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++) {
        uint16_t entry = screens[current_screen].buffer[i + VGA_WIDTH];
        screens[current_screen].buffer[i] = entry;
        vga_buffer[i] = entry;
    }

    for (int i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < VGA_HEIGHT * VGA_WIDTH; i++) {
        uint16_t entry = (uint16_t)' ' | (uint16_t)VGA_COLOR_WHITE << 8;
        screens[current_screen].buffer[i] = entry;
        vga_buffer[i] = entry;
    }
}

void k_putchar_at_cursor(const char c, uint8_t color) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        k_putchar(cursor_y * VGA_WIDTH + cursor_x, c, color);
        cursor_x++;
    }

    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y >= VGA_HEIGHT) {
        k_scroll();
        cursor_y = VGA_HEIGHT - 1; 
    }

    screens[current_screen].cursor_x = cursor_x;
    screens[current_screen].cursor_y = cursor_y;

    update_hardware_cursor(cursor_x, cursor_y);
}

void vga_init_screens() {
    for (int s = 0; s < NUM_SCREENS; s++) {
        for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
            screens[s].buffer[i] = (uint16_t)' ' | (uint16_t)VGA_COLOR_WHITE << 8;
        }
        screens[s].cursor_x = 0;
        screens[s].cursor_y = 0;
    }
    current_screen = 0;
    k_clear_screen();
}

void vga_switch_screen(int screen_id) {
    if (screen_id < 0 || screen_id >= NUM_SCREENS || screen_id == current_screen) {
        return;
    }

    screens[current_screen].cursor_x = cursor_x;
    screens[current_screen].cursor_y = cursor_y;

    current_screen = screen_id;

    cursor_x = screens[current_screen].cursor_x;
    cursor_y = screens[current_screen].cursor_y;

    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i] = screens[current_screen].buffer[i];
    }

    update_hardware_cursor(cursor_x, cursor_y);
}

void k_putstr(const char* str, uint8_t color, int x, int y) {
    int pos = y * VGA_WIDTH + x;
    for (int i = 0; str[i] != '\0'; i++) {
        k_putchar(pos, str[i], color);  
        pos++; 
        if (pos >= (VGA_WIDTH * VGA_HEIGHT)) break;
    }
}