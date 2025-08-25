#include <X11/Xlib.h>
#include <X11/XF86keysym.h>

static const unsigned int borderpx  = 2;
static const unsigned int snap      = 32;
static const unsigned int minwsz    = 1; /* for smfact */
static const int showbar            = 1;
static const char* statustext       = "cans-dwm";
static const int topbar             = 1;
static const char *fonts[]          = { "UbuntuMono Nerd Font:size=14" };
static const char dmenufont[]       = "UbuntuMono Nerd Font:size=14";

static const char col_black[]        = "#1c1b22";
static const char col_bright_black[] = "#4d4d4d";
static const char col_red[]          = "#ff6767";
static const char col_green[]        = "#61ffca";
static const char col_yellow[]       = "#ffca85";
static const char col_blue[]         = "#a277ff";
static const char col_magenta[]      = "#a277ff";
static const char col_cyan[]         = "#61ffca";
static const char col_white[]        = "#edecee";

static const char col_special_bg[]         = "#15141B";
static const char col_special_fg[]         = "#edecee";
static const char col_special_border[]     = "#61ffca";
static const char col_special_active_tab[] = "#21202e";
static const char col_special_selection_bg[] = "#1c1b22";

static const char *status_fg = col_special_fg;
static const char *status_bg = col_special_bg;
static const char *status_sep = col_blue;

static const char *colors[][3] = {
  [SchemeNorm] = { col_special_fg, col_special_bg, col_bright_black },
  [SchemeSel]  = { col_special_fg, col_special_bg, col_green }
};

static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
  { "Gimp",     NULL,       NULL,       0,            1,           -1 },
  { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

static const float mfact        = 0.55;
static const float smfact       = 0.00;
static const int nmaster        = 1;
static const int resizehints    = 1;
static const int lockfullscreen = 1;
static const int refreshrate    = 180;

static const Layout layouts[] = {
	{ "(tiled)",    tile },
	{ "(none)",     NULL },
	{ "(monocle)",  monocle },
};

#define MODKEY Mod4Mask

#define BASHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

#define TAGKEYS(KEY,TAG)                                  \
  { MODKEY, KEY, view, {.ui = 1 << TAG} },                \
  { MODKEY|ShiftMask, KEY, tagandview, {.ui = 1 << TAG} }

#define SPAWNKEYS(KEY, CMD)                       \
  { MODKEY, KEY, spawntofree, BASHCMD(CMD) },     \
  { MODKEY|ShiftMask, KEY, spawn, BASHCMD(CMD) }

static Key keys[] = {
  { MODKEY|ShiftMask, XK_q, spawn, BASHCMD("pkill dwm") },
  { MODKEY, XK_q, smartkillclient, {0} },
  SPAWNKEYS(XK_a, "kitty"),
  SPAWNKEYS(XK_f, "firefox"),
  SPAWNKEYS(XK_c, "code"),
  SPAWNKEYS(XK_o, "obs"),
  SPAWNKEYS(XK_y, "firefox -new-window https://youtube.com"),
  SPAWNKEYS(XK_g, "firefox -new-window https://chatgpt.com"),
  { 0, XK_Menu, spawn, BASHCMD("dmenu_run") },
  { 0, XK_Print, spawn, BASHCMD("maim") },
  { ControlMask, XK_Print, spawn, BASHCMD("maim -s") },
  { 0, XF86XK_AudioRaiseVolume, spawn, BASHCMD("wpctl set-volume @DEFAULT_SINK@ 3%+") },
  { 0, XF86XK_AudioLowerVolume, spawn, BASHCMD("wpctl set-volume @DEFAULT_SINK@ 3%-") },
  { 0, XF86XK_AudioMute, spawn, BASHCMD("wpctl set-mute @DEFAULT_SINK@ toggle") },

  { MODKEY, XK_Up, focusstack, {.i = -1} },
  { MODKEY, XK_Down, focusstack, {.i = +1} },
  { MODKEY, XK_Left, focusstack, {.i = -1} },
  { MODKEY, XK_Right, focusstack, {.i = +1} },

  { MODKEY|ShiftMask, XK_Up, movestack, {.i = -1} },
  { MODKEY|ShiftMask, XK_Down, movestack, {.i = +1} },
  { MODKEY|ShiftMask, XK_Left, movestack, {.i = -1} },
  { MODKEY|ShiftMask, XK_Right, movestack, {.i = +1} },

  { MODKEY|ControlMask, XK_Up, setsmfact, {.f = +0.01}},
  { MODKEY|ControlMask, XK_Down, setsmfact, {.f = -0.01}},
  { MODKEY|ControlMask, XK_Left, setmfact, {.f = -0.01} },
  { MODKEY|ControlMask, XK_Right, setmfact, {.f = +0.01} },

  { MODKEY, XK_Tab, focusnext, {0} },
  { MODKEY|ShiftMask, XK_Tab, focusprev, {0} },
  { MODKEY, XK_KP_Insert, focustag, {.i = -1} },
  { MODKEY, XK_KP_0, focustag, {.i = -1} },

  { MODKEY, XK_period, togglefloating, {0} },

  TAGKEYS(XK_1, 0),
  TAGKEYS(XK_2, 1),
  TAGKEYS(XK_3, 2),
  TAGKEYS(XK_4, 3),
  TAGKEYS(XK_5, 4),
  TAGKEYS(XK_6, 5),
  TAGKEYS(XK_7, 6),
  TAGKEYS(XK_8, 7),
  TAGKEYS(XK_9, 8),
};

static const Button buttons[] = {
  { ClkLtSymbol, 0, Button1, setlayout, {0} },
	{ ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]} },
	{ ClkWinTitle, 0, Button2, zoom, {0} },
	{ ClkClientWin, MODKEY, Button1, movemouse, {0} },
	{ ClkClientWin, MODKEY, Button2, togglefloating, {0} },
	{ ClkClientWin, MODKEY, Button3, resizeorfacts, {0} },
  { ClkClientWin, MODKEY|ShiftMask, Button3, resizemouse, {0} },
	{ ClkTagBar, 0, Button1, view, {0} },
	{ ClkTagBar, 0, Button3, toggleview, {0} },
	{ ClkTagBar, MODKEY, Button1, tag, {0} },
	{ ClkTagBar, MODKEY, Button3, toggletag, {0} },
};
