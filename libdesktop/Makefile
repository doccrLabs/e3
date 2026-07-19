#
# SPDX-License-Identifier: GPL-3.0-or-later
#
# Copyright (c) 2026 doccrLabs
#
# PROJECT: doccrOS
# FILE: user/libs/libdesktop/Makefile
#

CC  := x86_64-elf-gcc
AR  := x86_64-elf-ar
LIBC := ../include/libc

CFLAGS := -ffreestanding -nostdlib -fno-builtin -fno-stack-protector  \
          -fno-PIE -fno-pic -m64 -march=x86-64 -mno-red-zone          \
          -Wall -Wextra -std=gnu11 -D__doccr__                        \
          -I$(LIBC)/include                                           \
          -I.

SRCS := libdesktop.c
OBJS := $(SRCS:%.c=build/%.o)

all: build/libdesktop.a

build/%.o: %.c dt_input.h libdesktop.h | build
	$(CC) $(CFLAGS) -c $< -o $@

build/libdesktop.a: $(OBJS) | build
	$(AR) rcs $@ $(OBJS)

build:
	mkdir -p build

clean:
	rm -rf build

.PHONY: all clean