// SPDX-License-Identifier: GPL-2.0-only
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "bitdef.h"

#define KEYBOARD_PORT 0x60
#define PIC1_COMMAND  0x20
#define PIC_EOI       0x20

extern const char ascii_map[];
extern const u32 ascii_map_size;

void keyboard_handler(void);
char keyboard_get_char(void); 

#endif
