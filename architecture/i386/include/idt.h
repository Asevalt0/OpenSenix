// SPDX-License-Identifier: GPL-2.0-only
#ifndef IDT_H
#define IDT_H

#include "bitdef.h"

struct idt_entry {
    u16 base_low;    // The lower 16 bits of the address to jump to
    u16 selector;    // kernel segment selector (usually 0x08)
    u8  always0;     // This must always be zero
    u8  flags;        // Attribute flags (Present, Ring level, etc.)
    u16 base_high;   // The upper 16 bits of the address to jump to
} __attribute__((packed));

struct idt_ptr {
    u16 limit;
    u32 base;
} __attribute__((packed));


void idt_init(void);
void idt_set_gate(u8 num, u32 base, u16 sel, u8 flags);

#endif