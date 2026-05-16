// SPDX-License-Identifier: GPL-2.0-only
#include "bitdef.h"
#include "pm.h"

static u32    memory_bitmap[MAP_SIZE];
static size_t total_memory_pages = 0;
static size_t free_memory_pages = 0;

extern char _kernel_end[];

void pinit(void* boot_ptr) {
    struct pm* mmap = (struct pm*)0x00100000; 

    u32 kernel_end_page = ((u32)_kernel_end / 4096) + 1;

    while (mmap->size > 0) {
        if (mmap->type == 1) { 
            u32 start = (mmap->addr / 4096);
            u32 len   = (mmap->len / 4096);
            u32 end   = start + len;

            if (start < kernel_end_page) {
                start = kernel_end_page;
            }

            if (start >= end) {
                mmap = (struct pm*)((size_t)mmap + mmap->size + sizeof(mmap->size));
                continue;
            }

            for (u32 i = start; i < end; i++) {
                pmm_c_b(i); 
                total_memory_pages++;
                free_memory_pages++;
            }
        }
        mmap = (struct pm*)((size_t)mmap + mmap->size + sizeof(mmap->size));
    }
}

static inline void pmm_s_b(size_t page_frame) {
    memory_bitmap[page_frame / 32] |= (1U << (page_frame % 32));
}

static inline void pmm_c_b(size_t page_frame) {
    memory_bitmap[page_frame / 32] &= ~(1U << (page_frame % 32));
}

static inline int pmm_t_b(size_t page_frame) {
    return (memory_bitmap[page_frame / 32] & (1U << (page_frame % 32))) != 0;
}

void pm_init_low_memory(void) {
    memory_bitmap[0] = 0x0000FFFF;

    memory_bitmap[1] = 0x00000000;
    memory_bitmap[2] = 0x00000000;
    memory_bitmap[3] = 0x00000000;
    memory_bitmap[4] = 0x00000000;

    memory_bitmap[5] = 0xFFFFFFFF;
    memory_bitmap[6] = 0xFFFFFFFF;
    memory_bitmap[7] = 0xFFFFFFFF;

    total_memory_pages += 144;
    free_memory_pages  += 144;
}

int pm_free_page(void* page_addr) {
    size_t address = (size_t)page_addr;

    // make sure the address is aligned to a 4096 byte page bounds
    if (address % PAGE_SIZE != 0) {
        return -1; 
    }

    // Calculate exactly which page frame number this address represents
    size_t page_frame = address / PAGE_SIZE;

    pmm_c_b(page_frame);
    
    free_memory_pages++;
    return 0;
}

/*
 * scans the bitmap for the first available free page (0), marks it allocated (1),
 * and returns its physical memory address pointer.
 */

void* pm_alloc_page(void) {
    for (size_t i = 0; i < MAP_SIZE; i++) {
        if (memory_bitmap[i] == 0xFFFFFFFF) {
            continue;
        }

        for (int bit = 0; bit < 32; bit++) {
            u32 mask = (1U << bit);
            
           
            if ((memory_bitmap[i] & mask) == 0) {
                size_t page_frame = (i * 32) + bit;
                
           
                pmm_s_b(page_frame);
                free_memory_pages--;
      
                return (void*)(page_frame * PAGE_SIZE);
            }
        }
    }

    return (void*)0; // NULL
}
