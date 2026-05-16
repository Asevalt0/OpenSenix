#include "elapsed.h"
#include <x86intrin.h>

static size_t khz_ticks = 0;

void boot_time_init(size_t cpu_khz) {
    khz_ticks = cpu_khz;
}

size_t get_elapsed_ms(void) {
    if (khz_ticks == 0) {
        return 0; 
    }
    // Reads hardware clock cycles directly from the CPU
    size_t current_cycles = (size_t)__rdtsc();
    return current_cycles / khz_ticks;
}
