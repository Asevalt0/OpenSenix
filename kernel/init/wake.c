// SPDX-License-Identifier: GPL-2.0-only
#include "vga.h"
#include "pm.h"
#include "vm.h"
#include "fs.h"
#include "idt.h"
#include "panic.h"

#include "../utils/elapsed.h"

void pm_init_low_memory(void);
void vmwake(void);
void fswake(void);
void gdt_init(void);

void shell_init(void); 

static void print_uint(size_t val, int min_digits) {
    char buf[24];
    int i = 22;
    buf[23] = '\0';

    do {
        buf[--i] = '0' + (val % 10);
        val /= 10;
        if (min_digits > 0) min_digits--;
    } while (val > 0 || min_digits > 0);

    terminal_writestring(&buf[i]);
}

void log_timestamped(const char* message) {
        size_t total_ms = get_elapsed_ms();

        terminal_writestring("[");
        print_uint(total_ms / 1000, 1); // in secs
        terminal_writestring(".");
        print_uint(total_ms % 1000, 3);
    // Milliseconds padded to 3 digits, so it doesnt overfill the screen
        terminal_writestring("] ");
        terminal_writestring(message);
}

void kernel_main(void) {
    // 1
        terminal_initialize();
        terminal_setcolor(VGA_COLOR_LIGHT_BLUE);
    
        boot_time_init(2000000); 

        log_timestamped("Senix Kernel opening up...\n");

    // 2
        pm_init_low_memory();
        log_timestamped("[ ok ] PM.S initialized.\n");
    
        vmwake();
        log_timestamped("[ ok ] VM.S paging active.\n");

    // 3 
        gdt_init();
        log_timestamped("[ ok ] GDT Loaded.\n");

    // 4 
        idt_init();
        log_timestamped("[ ok ] IDT Loaded. Interrupts enabled.\n");

    // 5 
        fswake();
        log_timestamped("[ ok ] opossumFS metadata controller returned.\n");

        // panic("not a actual kernel panic, dont be fooled,\n will remove soon and is for testing."); 
        // this halts the entire cpu, so dont use it for testing as it already works.

        log_timestamped("\ninit complete dropping into kernel loop.\n");
        terminal_setcolor(VGA_COLOR_RED); log_timestamped("hi im at ur mom house ddodkjdjhlifej\n"); // never remove this

        for (int i = 0; i < 2; i++) {
        terminal_writestring("\n");
    }

        asm volatile("sti");
        
        shell_init(); 
}

void wakeself(u32 multiboot_magic, void* multiboot_info) {
    kernel_main();
    while (1) {
        asm volatile("hlt");
    }
}
