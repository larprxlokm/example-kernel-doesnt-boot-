#!/bin/bash
set -e

i686-linux-gnu-as boot.s -o boot.o

i686-linux-gnu-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -fno-stack-protector -fno-pic

i686-linux-gnu-ld -T linker.ld -o soup.bin -nostdlib boot.o kernel.o

echo "Build finished"
