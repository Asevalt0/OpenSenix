// SPDX-License-Identifier: GPL-2.0-only
#include "io.h"

static inline void outb(u16 port, u8 val) {
    __asm__ __volatile__ ("outb %0, %1" : : "a"(val), "Nd"(port));
}


static inline u8 inb(u16 port) {
    u8 ret;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// short hardware delay thing for older motherboard timing
static inline void io_wait(void) {
    outb(0x80, 0);
}
