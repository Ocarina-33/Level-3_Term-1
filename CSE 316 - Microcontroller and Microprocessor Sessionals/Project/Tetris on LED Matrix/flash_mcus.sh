#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

MCU="atmega32"
PROGRAMMER="usbasp"
F_CPU="1000000UL"

if [ -z "$1" ]; then
    echo "Usage: ./flash_mcus.sh [1|2]"
    echo "Example: ./flash_mcus.sh 1  (To compile and burn ATmega1_main.c)"
    echo "Example: ./flash_mcus.sh 2  (To compile and burn ATmega2_main.c)"
    exit 1
fi

if [ "$1" == "1" ]; then
    TARGET="ATmega1_main"
elif [ "$1" == "2" ]; then
    TARGET="ATmega2_main"
else
    echo "Invalid argument. Please specify 1 or 2."
    exit 1
fi

echo "=== Building and Flashing $TARGET ==="

echo "[1/4] Compiling C code..."
# Note: F_CPU is already defined in your C code, but setting it here is standard practice
avr-gcc -g -Os -mmcu=$MCU -c $TARGET.c

echo "[2/4] Linking..."
avr-gcc -g -mmcu=$MCU -o $TARGET.elf $TARGET.o

echo "[3/4] Generating .hex file..."
avr-objcopy -j .text -j .data -O ihex $TARGET.elf $TARGET.hex

echo "[4/4] Flashing via USBasp..."
# The -p m32 flag specifically tells avrdude it's an ATmega32
avrdude -c $PROGRAMMER -p m32 -U flash:w:$TARGET.hex:i

echo "=== SUCCESS: $TARGET flashed successfully! ==="
