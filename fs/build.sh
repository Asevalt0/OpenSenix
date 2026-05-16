#!/bin/bash
# Local filesystem build block
for file in fs/*.c; do
    [ -e "$file" ] || continue
    gcc $CCFLAGS $INCLUDES -c "$file" -o "build/$(basename ${file%.c}).o"
done