// SPDX-License-Identifier: GPL-2.0-only
#include "vga.h"
#include "bitdef.h"
#include "string.h"

u32 terminal_row;
u32 terminal_column;
u8 terminal_color;
u16* terminal_buffer = (u16*)VGA_MEMORY;

u8 vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

u16 vga_entry(char c, u8 color) {
    return (u16) c | (u16) color << 8;
}

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(u8 color) {
    terminal_color = color;
}

void terminal_putentryat(char c, u8 color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        terminal_row++;
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            terminal_row++;
        }
    }

    if (terminal_row >= VGA_HEIGHT)
        terminal_scroll();
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}

void backspace() {

}

void cursor(int show) {
    int current_index = terminal_row * 80 + terminal_column;

    volatile u16* vga_ptr = (volatile u16*)VGA_MEMORY;

    if (show) {
        vga_ptr[current_index] = '#' | (VGA_COLOR_LIGHT_BLUE << 8); 
    } else {
    
        vga_ptr[current_index] = ' ' | (VGA_COLOR_WHITE << 8);
    }
}

void terminal_scroll() {
    memmove(
        terminal_buffer,
        terminal_buffer + VGA_WIDTH,
        VGA_WIDTH * (VGA_HEIGHT - 1) * 2
    );

    // clear last line
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] =
            vga_entry(' ', terminal_color);
    }

    terminal_row = VGA_HEIGHT - 1;
}