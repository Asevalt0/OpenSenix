// SPDX-License-Identifier: GPL-2.0-only
#include "bitdef.h"


struct gdt_entry {
    u16 limit_low;
    u16 base_low;
    u8  base_middle;
    u8  access;
    u8  granularity;
    u8  base_high;
} __attribute__((packed));


struct gdt_ptr {
    u16 limit;
    u32 base;
} __attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_ptr   gp;

void gdt_set_gate(int num, u32 base, u32 limit, u8 access, u8 gran) {
    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access        = access;
}

void gdt_init(void) {
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base  = (u32)&gdt;

    gdt_set_gate(0, 0, 0, 0, 0);

    // base 0, Limit 4GB, Access 0x9A (Ring 0 Code), Granularity 0xCF (at 32-bit, 4KB blocks)
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    asm volatile("lgdt %0" : : "m"(gp));

    
    asm volatile(
        "ljmp $0x08, $.reload_segments\n"
        ".reload_segments:\n"
        "mov $0x10, %ax\n"
        "mov %ax, %ds\n"
        "mov %ax, %es\n"
        "mov %ax, %fs\n"
        "mov %ax, %gs\n"
        "mov %ax, %ss\n"
    );
}