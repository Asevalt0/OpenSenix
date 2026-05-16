/* SPDX-License-Identifier: GPL-2.0-only */
OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)
SECTIONS
{
  . = 1M;
  ImageBase = .;
  .text : {
    _text = .;
    *(.multiboot)
    *(.text)
    *(.text.*)
    *(.gnu.linkonce.t.*)
    _etext = .;
  }
  . = ALIGN(4096);
  .data : {
    _data = .;
    *(.rodata)
    *(.rodata.*)
    *(.data)
    *(.data.*)
    *(.sdata)
    *(.sdata.*)
    _edata = .;
  }
  . = ALIGN(4096);

  
  .bss : {
    _bss = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)
    _ebss = .;
  }

  . = ALIGN(4096);

  _kernel_end = .;

  .reloc : {
    *(.reloc)
  }
  .dynamic : { *(.dynamic) }
  .dynsym : { *(.dynsym) }
  .dynstr : { *(.dynstr) }
  .rel.dyn : { *(.rel.*) }
  /DISCARD/ : {
    *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*)
  }
}