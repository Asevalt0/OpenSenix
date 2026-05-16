// SPDX-License-Identifier: GPL-2.0-only
#ifndef TERMINAL_H
#define TERMINAL_H

#include "bitdef.h"

/* ================= VGA CONSTANTS ================= */
#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000U

extern u16 cursor_x;
extern u16 cursor_y;

enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

/* ================= VGA HELPERS ================= */
u8 vga_entry_color(enum vga_color fg, enum vga_color bg);
u16 vga_entry(char c, u8 color);

/* ================= TERMINAL STATE ================= */
extern u32 terminal_row;
extern u32 terminal_column;
extern u8 terminal_color;
extern u16* terminal_buffer;

/* ================= TERMINAL API ================= */
void terminal_initialize(void);
void terminal_setcolor(u8 color);
void terminal_putentryat(char c, u8 color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void cursor(int show);
void terminal_scroll();

#endif
