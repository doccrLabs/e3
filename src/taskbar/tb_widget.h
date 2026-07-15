/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * Copyright (c) 2026 doccrLabs
 *
 * PROJECT: e3
 * FILE: tb_widgets.h
 * CREATED BY: emex
 * MODIFIED BY: --
 *
 */

#pragma once

#include <sys/types.h>

// widget types
#define TB_WIDGET_NONE          0
#define TB_WIDGET_APP           1   // launches a program on click
#define TB_WIDGET_LABEL         2   // opens a popup window on click (app fills it via eXui)
#define TB_WIDGET_UPDATED_LABEL 3   // like LABEL but text/icon can be changed at runtime by an app

#define TB_WIDGET_MAX          16
#define TB_WIDGET_NAMELEN      32
#define TB_WIDGET_EXECLEN      64
#define TB_WIDGET_TEXTLEN      48   // displayed text (label / updated_label)

// icon placeholder — filled in later when icon loading is ready
typedef struct {
    int          loaded;        // 0 = no icon yet
    // void        *data;       // future: pointer to bmp_image_t or vad_image_t
    // int          w, h;
} tb_icon_t;

typedef struct {
    int          type;                      // TB_WIDGET_*
    char         name[TB_WIDGET_NAMELEN];   // internal id / button label fallback
    char         text[TB_WIDGET_TEXTLEN];   // visible label text (LABEL / UPDATED_LABEL)
    char         exec[TB_WIDGET_EXECLEN];   // path to launch   (APP / LABEL)
    tb_icon_t    icon;                      // icon placeholder

    // popup state (LABEL / UPDATED_LABEL)
    pid_t        popup_pid;     // pid of the popup owner app, -1 if none
    int          popup_w;       // desired popup width  (set by app on register)
    int          popup_h;       // desired popup height

    // runtime update flag (UPDATED_LABEL)
    int          dirty;         // set to 1 when text was changed, desktop clears it
} tb_widget_t;
