#!/bin/bash
# SPDX-License-Identifier: GPL-2.0-only
set -e

echo "== OpenSenix Modular Build =="

rm -rf build
mkdir -p build


export ROOT_DIR=$(pwd)

export INCLUDES="-I$ROOT_DIR/include \
-I$ROOT_DIR/architecture/i386/include \
-I$ROOT_DIR/kernel/drivers/video/include \
-I$ROOT_DIR/mm/include \
-I$ROOT_DIR/fs/include \
-I$ROOT_DIR/kernel/debug"

export CCFLAGS="-m32 -ffreestanding"

echo "Invoking sub-folder builds..."

./lib/build.sh
./fs/build.sh
./mm/build.sh
./kernel/build.sh

echo "Linking final kernel binary..."
ld -m elf_i386 -T linker/elf_i386_efi.lds \
    build/mb.o \
    build/wake.o \
    build/elapsed.o \
    build/kpanic.o \
    build/vga.o \
    build/gdt.o \
    build/idt.o \
    build/pm.o \
    build/vm.o \
    build/fs.o \
    build/shell.o \
    build/keyboard.o \
    build/string.o \
    -o build/kernel.elf

echo "Building ISO..."
rm -rf iso && mkdir -p iso/boot/grub
cp build/kernel.elf iso/boot/kernel.elf

cat > iso/boot/grub/grub.cfg <<EOF
set timeout=0
set default=0
menuentry "OpenSenix" {
    multiboot /boot/kernel.elf
    boot
}
EOF

grub-mkrescue -o opensenix.iso iso >/dev/null 2>&1
echo "Done -> opensenix.iso"