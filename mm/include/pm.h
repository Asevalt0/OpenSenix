// SPDX-License-Identifier: GPL-2.0-only
#ifndef PM_H
#define PM_H

#include <stddef.h>
#include "bitdef.h"

struct pm 
{
    u32 size;   
    u64 addr;   
    u64 len;    
    u32 type;   
} __attribute__((packed)); 

#define MAP_SIZE    32768
#define PAGE_SIZE   4096

void pinit(void* boot_ptr);
static inline int pmm_t_b(size_t page_frame);
static inline void pmm_c_b(size_t page_frame);
void* pm_alloc_page(void);

int pm_free_page(void* page_addr);

#endif