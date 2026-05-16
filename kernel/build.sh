#!/bin/bash
# Local core kernel build block

# Compile flat directory files
gcc $CCFLAGS $INCLUDES -c kernel/utils/elapsed.c -o build/elapsed.o
gcc $CCFLAGS $INCLUDES -c kernel/debug/panic.c -o build/kpanic.o

gcc $CCFLAGS $INCLUDES -c kernel/shell.c -o build/shell.o
gcc $CCFLAGS $INCLUDES -c kernel/drivers/video/vga.c -o build/vga.o
gcc $CCFLAGS $INCLUDES -c kernel/init/wake.c -o build/wake.o
gcc $CCFLAGS $INCLUDES -c kernel/init/idt.c -o build/idt.o

gcc $CCFLAGS $INCLUDES -c kernel/init/gdt.c -o build/gdt.o

gcc $CCFLAGS $INCLUDES -c kernel/drivers/keyboard/keyboard.c -o build/keyboard.o

nasm -f elf32 kernel/init/mb.s -o build/mb.o