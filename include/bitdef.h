// SPDX-License-Identifier: GPL-2.0-only

#ifndef BITDEF_H
#define BITDEF_H

typedef unsigned char          u8;
typedef unsigned short         u16;
typedef unsigned int           u32;
typedef unsigned long long int u64;

#ifdef __x86_64__
    typedef u64 uintptr_t;
    typedef u64 size_t;
    typedef long long int ptrdiff_t; /* Signed difference between pointers */
    typedef long long int ssize_t;   /* Signed size type for error codes */
#else
    typedef u32 uintptr_t;
    typedef u32 size_t;
    typedef int           ptrdiff_t; /* Signed difference between pointers */
    typedef int           ssize_t;   /* Signed size type for error codes */
#endif

// not gonna use these for now but they are probably a good thing to leave in :)
#define SET_BIT(num, bit)   ((num) |= (1U << (bit)))
#define CLEAR_BIT(num, bit) ((num) &= ~(1U << (bit)))
#define TEST_BIT(num, bit)  (((num) >> (bit)) & 1U)

#endif
