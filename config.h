#include <X11/Xlib.h>
#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "UbuntuMono Nerd Font:size=14" };
static const char dmenufont[]       = "UbuntuMono Nerd Font:size=14";

static const char col_bg[]       = "#15141B";
static const char col_fg[]       = "#edecee";
static const char col_border[]   = "#61ffca";

static const char *colors[][3]      = {
    [SchemeNorm] = { col_fg, col_bg, col_border },
    [SchemeSel]  = { col_fg, col_bg, "#a277ff" },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define BASHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg, "-sb", col_border, "-sf", col_border, NULL };
static const char *killcmd[]  = { "st", NULL };

// static const char *killcmd[] = { "/home/you/.config/custom-kill.sh", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *firefoxcmd[] = { "firefox", NULL };
static const char *ytcmd[] = { "firefox", "-new-window", "https://youtube.com", NULL };
static const char *chatgptcmd[] = { "firefox", "-new-window", "https://chatgpt.com", NULL };
// static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *screenshotcmd[] = { "maim", NULL };
static const char *screenshotselectcmd[] = { "maim", "-s", NULL };

static const char *volup[]   = { "wpctl", "set-volume", "@DEFAULT_SINK@", "3%+", NULL };
static const char *voldown[] = { "wpctl", "set-volume", "@DEFAULT_SINK@", "3%-", NULL };
static const char *volmute[] = { "wpctl", "set-mute", "@DEFAULT_SINK@", "toggle", NULL };

/* keys */
static Key keys[] = {
    { MODKEY,                       XK_q,      spawn,          {.v = killcmd } },
    { MODKEY,                       XK_a,      spawn,          {.v = termcmd } },
    { MODKEY,                       XK_f,      spawn,          {.v = firefoxcmd } },
    { MODKEY,                       XK_y,      spawn,          {.v = ytcmd } },
    { MODKEY,                       XK_g,      spawn,          {.v = chatgptcmd } },

    { MODKEY|ShiftMask,             XK_a,      spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = firefoxcmd } },

    { 0,                            XK_Menu,   spawn,          {.v = dmenucmd } },
    { 0,                            XK_Print,  spawn,          {.v = screenshotcmd } },
    { ControlMask,                  XK_Print,  spawn,          {.v = screenshotselectcmd } },
    { 0, XF86XK_AudioRaiseVolume, spawn, {.v = volup } },
    { 0, XF86XK_AudioLowerVolume, spawn, {.v = voldown } },
    { 0, XF86XK_AudioMute,        spawn, {.v = volmute } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = killcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

