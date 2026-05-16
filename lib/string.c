// SPDX-License-Identifier: GPL-2.0-only
#include "string.h"
#include "bitdef.h"

void *memset(void *dest, int val, size_t count) {
    u8 *ptr = (u8 *)dest;
    while (count--) {
        *ptr++ = (u8)val;
    }
    return dest;
}

void *memcpy(void *dest, const void *src, size_t count) {
    u8 *d = (u8 *)dest;
    const u8 *s = (const u8 *)src;
    while (count--) {
        *d++ = *s++;
    }
    return dest;
}

size_t strlen(const char *str) {
    size_t i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

void strcpy(char *dest, const char *src) {
    while ((*dest++ = *src++) != '\0');
}

int strcmp(const char *a, const char *b) {
    while (*a && (*a == *b)) {
        a++;
        b++;
    }

    return *(const unsigned char*)a - *(const unsigned char*)b;
}

void *memmove(void *dest, const void *src, size_t count) {
    u8 *d = (u8 *)dest;
    const u8 *s = (const u8 *)src;

    if (d < s) {
        while (count--) *d++ = *s++;
    } else {
        d += count;
        s += count;
        while (count--) *--d = *--s;
    }

    return dest;
}