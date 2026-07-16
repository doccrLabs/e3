/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * Copyright (c) 2026 doccrLabs
 *
 * PROJECT: e3
 * FILE: comp.c
 * CREATED BY: emex
 * MODIFIED BY: Offihito
 *
 */

#include "comp.h"
#include <sys/fb.h>
#include <unistd.h>

static int g_fd = -1;
static int g_w = 0;
static int g_h = 0;
static unsigned int *g_buf = 0;
static unsigned int g_stride = 0;

// fixed by @offihito

void comp_init(int fb_fd, int w, int h) {
	(void)w;
    (void)h;
    g_fd = fb_fd;

    fb_info_t info;
    if (ioctl(g_fd, FB_IOCTL_GET_INFO, &info) < 0) return;

    g_w = (int)info.width;
    g_h = (int)info.height;
    g_stride = info.pitch / 4;

    unsigned long vaddr = 0;
    if (ioctl(g_fd, FB_IOCTL_MAP, &vaddr) < 0) return;

    g_buf = (unsigned int *)vaddr;
}

void comp_capture(void) {
	//
}

void comp_fill(
	int x,
	int y,
	int w,
	int h,
	unsigned int color
){
    if (!g_buf) return;
    for (int dy = 0; dy < h; dy++)
    {
        int py = y + dy;
        if (py < 0 || py >= g_h) continue;
        unsigned int *row = g_buf + (unsigned)py * g_stride;

        int x0 = x < 0 ? 0 : x;
        int x1 = (x + w) > g_w ? g_w : (x + w);
        for (int px = x0; px < x1; px++) row[px] = color;
    }
}

unsigned int comp_get(
	int x,
	int y
){
    if (
    	!g_buf ||
     	x < 0 ||
      	x >= g_w ||
       	y < 0 ||
        y >= g_h
    ) return 0;

    return g_buf[(unsigned)y * g_stride + (unsigned)x];
}

void comp_set(
	int x,
	int y,
	unsigned int c
) {
    if (
    	!g_buf ||
     	x < 0 ||
      	x >= g_w ||
       	y < 0 ||
        y >= g_h
    ) return;

    g_buf[(unsigned)y * g_stride + (unsigned)x] = c;
}

void comp_put_row(
	int x,
	int y,
	const unsigned int *row,
	int len
) {
    if (
    	!g_buf ||
     	y < 0 ||
      	y >= g_h
    ) return;

    unsigned int *dst = g_buf + (unsigned)y * g_stride;

    for (int i = 0; i < len; i++)
    {
        int px = x + i;
        if (px >= 0 && px < g_w) dst[px] = row[i];
    }
}

void
comp_copy_rect(
	int src_x,
	int src_y,
	int dst_x,
	int dst_y,
	int w,
	int h
){
    if (
    	!g_buf ||
     	w <= 0 ||
        h <= 0
    ) return;

    int ystep = (dst_y <= src_y) ? 1 : -1;
    int r0 = (ystep == 1) ? 0 : h - 1;
    int r1 = (ystep == 1) ? h : -1;

    for (int r = r0; r != r1; r += ystep)
    {
        int sy = src_y + r, dy = dst_y + r;
        if (
        	sy < 0 ||
         	sy >= g_h ||
          	dy < 0 ||
           	dy >= g_h
        ) continue;

        unsigned int *srow = g_buf + (unsigned)sy * g_stride;
        unsigned int *drow = g_buf + (unsigned)dy * g_stride;

        int xstep = (dst_x <= src_x) ? 1 : -1;
        int c0 = (xstep == 1) ? 0 : w - 1;
        int c1 = (xstep == 1) ? w : -1;

        for (int c = c0; c != c1; c += xstep)
        {
            int spx = src_x + c, dpx = dst_x + c;
            if (spx >= 0 && spx < g_w && dpx >= 0 && dpx < g_w) drow[dpx] = srow[spx];
        }
    }
}

void comp_put_pixels(
	int x,
	int y,
	int w,
	int h,
	const unsigned int *pixels
) {
    if (!g_buf || !pixels) return;
    for (int row = 0; row < h; row++)
    {
        int py = y + row;
        if (py < 0 || py >= g_h) continue;
        unsigned int *dst = g_buf + (unsigned)py * g_stride;

        for (int col = 0; col < w; col++)
        {
            int px = x + col;
            if (px >= 0 && px < g_w) dst[px] = pixels[row * w + col];
        }
    }
}

void comp_flush(void)
{
    if (!g_buf || g_fd < 0) return;
    ioctl(g_fd, FB_IOCTL_FLUSH, 0);
}

int comp_w(void) { return g_w; }

int comp_h(void) { return g_h; }
