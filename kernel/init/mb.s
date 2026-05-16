; SPDX-License-Identifier: GPL-2.0-only

; --- Multiboot Header Section ---
section .multiboot
align 4
    dd 0x1BADB002             ; Magic number for Multiboot
    dd 0x00                   ; Flags
    dd -(0x1BADB002 + 0x00)   ; Checksum to prove validity

; --- Stack Allocation Section ---
section .bss
align 16
stack_bottom:
    resb 16384                
stack_top:


section .text
global _start
extern wakeself
extern keyboard_handler        

_start:
    ; 1. Set up the stack pointer register so code can execute functions
    mov esp, stack_top

    ; 2. Clear out the CPU EFLAGS register to a known clean state
    push 0
    popf

    ; 3. Jump straight out of assembly mode and into the kernelll
    push ebx
    call wakeself

.halt_loop:
    hlt                       ; to be safe If wakeself returns, halt the CPU safely
    jmp .halt_loop

global idt_load
idt_load:
    mov edx, [esp + 4]    
    lidt [edx]                ; the Interrupt Descriptor Table pointer
    ret

global keyboard_isr_wrapper  

keyboard_isr_wrapper:
    pusha                
    cld                    

    mov ebp, esp              
    and esp, 0xFFFFFFF0       
    
    call keyboard_handler     
    
    mov esp, ebp              
    popa                    
    iretd

section .note.GNU-stack noalloc noexec nowrite progbits