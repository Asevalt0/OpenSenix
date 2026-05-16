// SPDX-License-Identifier: GPL-2.0-only
#include "io.h"
#include "keyboard.h"
#include "bitdef.h"
#include "vga.h"

// Standard Scan Code
const char ascii_map[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',    /* 0x00 - 0x09 */
  '9', '0', '-', '=', '\b',                            /* 0x0A - 0x0E */
  '\t',                                                /* 0x0F (Tab)  */
  'q', 'w', 'e', 'r',                                  /* 0x10 - 0x13 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',        /* 0x14 - 0x1C */
    0,                                                 /* 0x1D (Control) */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',    /* 0x1E - 0x27 */
 '\'', '`',   0,                                       /* 0x28 - 0x2A (Left Shift) */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.',    /* 0x2B - 0x34 */
  '/',   0,                                            /* 0x35 - 0x36 (Right Shift) */
  '*',
    0,                                                 /* 0x38 (Alt) */
  ' '                                                  /* 0x39 (Space bar) */
};

const u32 ascii_map_size = sizeof(ascii_map);

/*
1. Only process when a key is pressed down (ignore key-release break codes)
2. Make sure the scancode exists within the array mapping bounds
3. If it maps to a real character, print it directly to the screen!
4. Signal the EOI back to the primary PIC so it listens again
*/

void keyboard_handler(void) {
    
    u8 scancode = inb(KEYBOARD_PORT);

    if (!(scancode & 0x80)) {
        if (scancode < ascii_map_size) {
            char inp_ascii = ascii_map[scancode];
            
            if (inp_ascii != 0) { 
                terminal_putchar(inp_ascii); 
            }
        }
    }

    outb(PIC1_COMMAND, PIC_EOI);
}