// SPDX-License-Identifier: GPL-2.0-only
#include "panic.h"
#include "vga.h"

void panic(const char* msg) {
    terminal_setcolor(VGA_COLOR_RED);

    terminal_writestring("kpanic: ");
    terminal_writestring(msg);

    while (1) {
        __asm__ volatile ("hlt");
    }
}