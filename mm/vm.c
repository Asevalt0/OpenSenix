// SPDX-License-Identifier: GPL-2.0-only
#include "pm.h"

static u32* page_directory = (void*)0;

static u32* first_page_table = (void*)0;
static u32* second_page_table = (void*)0;

void vmwake(void) {
    page_directory    = (u32*)pm_alloc_page();
    first_page_table  = (u32*)pm_alloc_page();
    second_page_table = (u32*)pm_alloc_page();


    for (int i = 0; i < 1024; i++) {
        page_directory[i] = 0x00000002;
        first_page_table[i] = 0x00000000;
        second_page_table[i] = 0x00000000;
    }


    for (unsigned int i = 0; i < 1024; i++) {
        first_page_table[i] = (i * 4096) | 0x03;
    }

  
    for (unsigned int i = 0; i < 1024; i++) {
        second_page_table[i] = (0x00400000 + (i * 4096)) | 0x03;
    }

   
    page_directory[0] = ((u32)first_page_table)  | 0x03; 
    page_directory[1] = ((u32)second_page_table) | 0x03; 

    asm volatile("mov %0, %%cr3" : : "r"(page_directory));

    u32 cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000; 
    asm volatile("mov %0, %%cr0" : : "r"(cr0));
}