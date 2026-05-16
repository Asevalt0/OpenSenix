// SPDX-License-Identifier: GPL-2.0-only
#include "idt.h"
#include "io.h"    

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void idt_load(u32 pointer);
extern void keyboard_isr_wrapper(void);

void pic_remap(void) {
    outb(0x20, 0x11); io_wait(); // Start initialization for Master PIC
    outb(0xA0, 0x11); io_wait(); // Start initialization for Slave PIC

    outb(0x21, 0x20); io_wait(); // Map primary IRQs to IDT gates 32-39
    outb(0xA1, 0x28); io_wait(); // Map secondary IRQs to IDT gates 40-47

    outb(0x21, 0x04); io_wait(); // Tell primary PIC that primary is at IRQ2
    outb(0xA1, 0x02); io_wait(); // Tell secondary PIC its identity

    outb(0x21, 0x01); io_wait(); 
    outb(0xA1, 0x01); io_wait(); 

    outb(0x21, 0xFD); io_wait(); 
    outb(0xA1, 0xFF); io_wait();
}

void idt_set_gate(u8 num, u32 base, u16 sel, u8 flags) {
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_init(void) {
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (u32)&idt;

  
    for(int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0x08, 0x00);
    }

    pic_remap();

    __attribute__((naked)) void quick_test_handler(void) {
    asm volatile(
        "pushal\n"
        "mov $0x20, %al\n"  
        "out %al, $0x20\n"
        "popal\n"
        "iretd\n"
    );
}

    idt_set_gate(33, (u32)keyboard_isr_wrapper, 0x08, 0x8E);

    idt_load((u32)&idtp);
}