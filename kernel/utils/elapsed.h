#ifndef ELAPSED_H
#define ELAPSED_H

#include "bitdef.h"

void boot_time_init(size_t cpu_khz);
size_t get_elapsed_ms(void);

#endif