/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * Copyright (c) 2026 doccrLabs
 *
 * PROJECT: e3
 * FILE: entries.c
 * CREATED BY: emex
 * MODIFIED BY: --
 *
 */

#include "entries.h"
#include <string.h>

//all app entries till we have a parser so it reads from a config
static tb_widget_t s_entries[] =
{
    {
        .type          = TB_WIDGET_APP,
        .name          = "term",
        .text          = "term",
        .exec          = "/emr/system/terminal.emx",
        .icon          = { .loaded = 0 },
        .popup_pid     = -1,
        .popup_w       = 0,
        .popup_h       = 0,
        .dirty         = 0,
    },
    {
        .type          = TB_WIDGET_APP,
        .name          = "fm",
        .text          = "fm",
        .exec          = "/emr/system/fm.elf",
        .icon          = { .loaded = 0 },
        .popup_pid     = -1,
        .popup_w       = 0,
        .popup_h       = 0,
        .dirty         = 0,
    },
    {
        .type          = TB_WIDGET_APP,
        .name          = "gears",
        .text          = "gears",
        .exec          = "/bin/gears.elf",
        .icon          = { .loaded = 0 },
        .popup_pid     = -1,
        .popup_w       = 0,
        .popup_h       = 0,
        .dirty         = 0,
    },
    {
        .type          = TB_WIDGET_APP,
        .name          = "sysinfo",
        .text          = "sysinfo",
        .exec          = "/emr/system/sysinfo.elf",
        .icon          = { .loaded = 0 },
        .popup_pid     = -1,
        .popup_w       = 0,
        .popup_h       = 0,
        .dirty         = 0,
    },
};

#define ENTRIES_COUNT (int)(sizeof(s_entries) / sizeof(s_entries[0]))

tb_widget_t *entries_get(int *out_count)
{
    if (out_count) *out_count = ENTRIES_COUNT;
    return s_entries;
}

// to load icons is implemented but not used xd
void taskbar_load_entry_icon(int index)
{
    if (index < 0 || index >= ENTRIES_COUNT) return;
    //i dont want to have icons yet cuz bmp doesnt support transparency but in some time i add png ig
    (void)index;
}
