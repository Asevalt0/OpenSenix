#!/bin/bash
# Local helper library build block
for file in lib/*.c; do
    [ -e "$file" ] || continue
    gcc $CCFLAGS $INCLUDES -c "$file" -o "build/$(basename ${file%.c}).o"
done