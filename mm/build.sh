#!/bin/bash
# Local memory management build block

for file in mm/*.c; do
    [ -e "$file" ] || continue
    gcc $CCFLAGS $INCLUDES -c "$file" -o "build/$(basename ${file%.c}).o"
done