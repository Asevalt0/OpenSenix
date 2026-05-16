// SPDX-License-Identifier: GPL-2.0-only

#ifndef STR_H
#define STR_H

#include "bitdef.h"

// non returning funcs

void *memset(void *dest, int val, size_t count);

void *memcpy(void *dest, const void *src, size_t count);

void strcpy(char *dest, const char *src);

void *memmove(void *dest, const void *src, size_t count);

// returning funcs

size_t strlen(const char *str);

int strcmp(const char *a, const char *b);


#endif
