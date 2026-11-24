#!/bin/bash

# Enable extended globbing for pattern matching
shopt -s extglob

for file in !(*.sh|*.g4|*.lib|*.cpp|*.h|*.hpp|*.pdf|compile_commands.json); do
    if [[ -f "$file" ]]; then
        rm -f "$file"
    fi
done

rm -rf output
