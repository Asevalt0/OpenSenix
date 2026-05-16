// SPDX-License-Identifier: GPL-2.0-only
#include "shell.h"
#include "vga.h"
#include "envs.h"
#include "string.h"

void cmd_help(void);
void cmd_version(void);
void cmd_clear(void);

static const shell_command_t command_table[] = {
    {"help",    "Display all available shell commands", cmd_help},
    {"version", "Print OpenSenix kernel version details", cmd_version},
    {"clear",   "Clear the visual screen buffer",        cmd_clear}
};

#define COMMAND_COUNT (sizeof(command_table) / sizeof(shell_command_t))


void cmd_help(void) {
    terminal_writestring("Available commands:");
    for (size_t i = 0; i < COMMAND_COUNT; i++) {
        terminal_writestring("  ");
        terminal_writestring(command_table[i].name);
        terminal_writestring(" - ");
        terminal_writestring(command_table[i].description);
        terminal_writestring("\n");
    }
}

void cmd_version(void) {
    terminal_writestring(NAME);
    terminal_writestring(" Kernel v0.05\n");
    terminal_writestring("\n\nCopyright (C) OpenSenix Kernel. All rights reserved.\n");
}

void cmd_clear(void) {
    terminal_initialize();
}

void shell_run_command(const char *cmd) {
    if (strlen(cmd) == 0) return;

    for (size_t i = 0; i < COMMAND_COUNT; i++) {
        if (strcmp(cmd, command_table[i].name) == 0) {
            command_table[i].function(); 
            return;
        }
    }

    terminal_writestring("Error: Command '");
    terminal_writestring(cmd);
    terminal_writestring("' not recognized. Type 'help'.");
}


extern void shell_init() {
    terminal_setcolor(VGA_COLOR_WHITE);
    cmd_version();
}