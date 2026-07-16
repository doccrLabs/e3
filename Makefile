#
# SPDX-License-Identifier: GPL-3.0-or-later
#
# Copyright (c) 2026 doccrLabs
#
# FILE: Makefile
# CREATED BY: emex
# MODIFIED BY: --
#
#

CC     := x86_64-elf-gcc
LD     := x86_64-elf-ld
LIBC   := ../../libc
LIBS_D := ../../libs

CFLAGS := -ffreestanding -nostdlib -fno-builtin -fno-stack-protector    \
          -fno-PIE -fno-pic -m64 -march=x86-64 -mno-sse -mno-sse2       \
          -mno-mmx -mno-red-zone -Wall -Wextra -std=gnu11 -D__doccr__   \
          -I$(LIBC)/include                                             \
          -I$(LIBS_D)/libfont                                           \
          -I$(LIBS_D)/libbmp

LDFLAGS := -nostdlib -static -no-pie -T ../../user.ld

LIBS := $(LIBS_D)/libfont/libfont.a       \
        $(LIBS_D)/libbmp/libbmp.a

OBJS := build/desktop.o \
		build/desktop_input_dispatch.o \
        build/compositor/comp.o \
        build/cmd/cmd.o \
        build/bg/bg.o \
        build/win/win.o \
        build/cursor/cursor.o \
        build/render/render.o \
        build/input/input.o \
        build/taskbar/taskbar.o \
        build/taskbar/entries.o

all: libs clean build/desktop.elf

build/desktop.elf: $(OBJS) $(LIBC)/build/crt0.o $(LIBC)/build/libc.a $(LIBS)
	$(LD) $(LDFLAGS) $(LIBC)/build/crt0.o $(OBJS) $(LIBS) $(LIBC)/build/libc.a -o $@

build/desktop.o:                    src/desktop.c                   ; $(CC) $(CFLAGS) -c $< -o $@
build/compositor/comp.o:            src/compositor/comp.c           ; $(CC) $(CFLAGS) -c $< -o $@
build/bg/bg.o:                      src/bg/bg.c                     ; $(CC) $(CFLAGS) -c $< -o $@
build/win/win.o:                    src/win/win.c                   ; $(CC) $(CFLAGS) -c $< -o $@
build/desktop_input_dispatch.o:     src/desktop_input_dispatch.c    ; $(CC) $(CFLAGS) -c $< -o $@
build/cursor/cursor.o:              src/cursor/cursor.c             ; $(CC) $(CFLAGS) -c $< -o $@
build/render/render.o:              src/render/render.c             ; $(CC) $(CFLAGS) -c $< -o $@
build/input/input.o:                src/input/input.c               ; $(CC) $(CFLAGS) -c $< -o $@
build/taskbar/taskbar.o:            src/taskbar/taskbar.c           ; $(CC) $(CFLAGS) -c $< -o $@
build/taskbar/entries.o:            src/taskbar/entries.c           ; $(CC) $(CFLAGS) -c $< -o $@
build/cmd/cmd.o:                    src/cmd/cmd.c                   ; $(CC) $(CFLAGS) -c $< -o $@

$(LIBC)/build/crt0.o $(LIBC)/build/libc.a:
	$(MAKE) -C $(LIBC)

libs:
	$(MAKE) -C $(LIBS_D)/libfont
	$(MAKE) -C $(LIBS_D)/libbmp

clean:
	rm -f build/*.o build/compositor/*.o build/bg/*.o build/win/*.o build/cursor/*.o build/render/*.o build/input/*.o build/cmd/*.o build/taskbar/*.o build/desktop.elf

.PHONY: all libs clean
