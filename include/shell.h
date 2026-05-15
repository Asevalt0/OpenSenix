#ifndef SHELL_H
#define SHELL_H

#include "bitdef.h"

typedef void (*shell_cmd_func_t)(void);

typedef struct {
    const char *name;
    const char *description;
    shell_cmd_func_t function;
} shell_command_t;

void shell_init(void);
void shell_update(void);

#endif
