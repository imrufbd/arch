/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "UbuntuMono Nerd Font:size=10" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#bf616a"; /* tag color #eeeeee #bf616a*/
static const char col_cyan[]        = "#0a0f14"; /* bar color #005577 #0a0f14*/
static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff0000";
static const char col_yellow[]      = "#ffff00";
static const char col_white[]       = "#ffffff";
static const char col_y1[]          = "#191919";
static const char col_y2[]          = "#fea63c"; /* #fea63c */

static const char *colors[][8]      = {
	/*					fg         bg          border   */
	[SchemeNorm] =	 { col_gray3, col_gray1,   col_gray2 },
	[SchemeSel]  =	 { col_gray4, col_cyan,    col_cyan },
	[SchemeWarn] =	 { col_black, col_yellow,  col_red },
	[SchemeUrgent]=	 { col_cyan,  "#7197e7",   col_gray1 },
                     { "#7197e7", col_black,   col_black },
                     { col_cyan,  "#A77AC4",   col_gray1 },
                     { "#A77AC4", col_black,   col_black },
                     { col_cyan,  "#8be9fd",    col_gray1 },
                     { "#bf616a", col_black,   col_black },
};

/* tagging */
static const char *tags[] = { "","","","" };

/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "st",      NULL,     NULL,           0,         0,          1,          -1,        -1 },
	{ "qutebrowser", NULL,      NULL,     1 << 1,       0,           0,         0,        -1 },
    { "mpv",         NULL,      NULL,     1 << 2,       1,                      1,        -1 },
    { "MPlayer",     NULL,      NULL,     1 << 2,       1,                      1,        -1 },
	{ "libreoffice", NULL,      NULL,     1 << 3,       0,           0,         0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         1,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[B]",      bstack },
};

/* key definitions */
#define MODKEY Mod1Mask
#define MOD2   Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define CMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "st", NULL };
static const char *fcmd[] = { "st", "-e", "nnn", NULL };
static const char *fcmd2[] = { "pcmanfm", NULL };
static const char *fcmd3[] = { "st", "-e", "ranger", NULL };
static const char *bcmd[] = { "qutebrowser", NULL };
static const char *bcmd2[] = { "firefox", NULL };
static const char *bcmd3[] = { "st", "-e", "elinks", NULL };
static const char *dbang[] = { "dbang", NULL };
static const char *ips[] = { "i3exit", "suspend", NULL };
static const char *ipr[] = { "i3exit", "reboot", NULL };
static const char *iph[] = { "i3exit", "shutdown", NULL };
static const char *ipl[] = { "i3exit", "lock", NULL };
static const char *pmenu[] = { "powermenu", NULL };
static const char *upvol[] = { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *downvol[] = { "pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *mutevol[] = { "pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *brdec[] = { "brightnessctl", "s", "5%-", NULL };
static const char *brinc[] = { "brightnessctl", "s", "+5%", NULL };
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-i", "-p", ":>_", NULL };
/* static const char *rbang[] = { "rbang", NULL }; */
/* static const char *roficmd[] = { "rofi", "-show", "combi", NULL }; */

#include <X11/XF86keysym.h>
#include "movestack.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_semicolon,     spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_slash,         spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_o,             spawn,          {.v = fcmd } },
	{ MODKEY,                       XK_p,             spawn,          {.v = fcmd2 } },
	{ MOD2,                         XK_o,             spawn,          {.v = fcmd3 } },
	{ MODKEY,                       XK_i,             spawn,          {.v = bcmd } },
	{ MOD2,                         XK_i,             spawn,          {.v = bcmd2 } },
	{ MODKEY,                       XK_n,             spawn,          {.v = bcmd3 } },
	{ MOD2,                         XK_semicolon,     spawn,          {.v = dbang } },
	{ MODKEY,                       XK_b,             togglebar,      {0} },
	{ MODKEY,                       XK_j,             focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,             focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,             incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,             incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,             setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,             setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,             movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,             movestack,      {.i = -1 } },
	{ MOD2,                         XK_j,             movestack,      {.i = +1 } },
	{ MOD2,                         XK_k,             movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return,        zoom,           {0} },
	{ MODKEY,                       XK_Tab,           view,           {0} },
	{ ControlMask,                  XK_space,         view,           {0} },
	{ MODKEY,                       XK_y,             killclient,     {0} },
	{ MODKEY,                       XK_t,             setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,             setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,             setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_t,             setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,         setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,         togglefloating, {0} },
	{ MODKEY,                       XK_0,             view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,             tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,         focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,        focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,         tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,        tagmon,         {.i = +1 } },
    { MODKEY|ControlMask,           XK_l,             shiftview,      { .i = +1 } },
    { MODKEY|ControlMask,           XK_h,             shiftview,      { .i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,              quit,           {0} },
	{ MODKEY|ShiftMask,             XK_x,              spawn,          {.v = pmenu } },
	{ MODKEY|ShiftMask,             XK_s,              spawn,          {.v = ips } },
	{ MODKEY|ShiftMask,             XK_r,              spawn,          {.v = ipr } },
	{ MODKEY|ShiftMask,             XK_h,              spawn,          {.v = iph } },
	{ MODKEY|ShiftMask,             XK_l,              spawn,          {.v = ipl } },
	{ MODKEY|ShiftMask,             XK_m,              spawn,          CMD("st -e ncmpcpp") },
	{ MODKEY|ShiftMask,             XK_n,              spawn,          CMD("leafpad new.txt") },
    { 0,                     XF86XK_MonBrightnessUp,   spawn,          {.v = brinc } },
    { 0,                     XF86XK_MonBrightnessDown, spawn,          {.v = brdec } },
	{ 0,                            XF86XK_Calculator, spawn,          CMD("= --dmenu=dmenu -- -l 3 -c") }, /* menu-calc script */
    { 0,                     XF86XK_AudioLowerVolume,  spawn,          {.v = downvol } },
    { 0,                     XF86XK_AudioMute,         spawn,          {.v = mutevol } },
    { 0,                     XF86XK_AudioRaiseVolume,  spawn,          {.v = upvol   } },
	{ 0,                            XK_Print,          spawn,          CMD("maim ~/ss/$(date +%d%h%T).png") },
	{ ShiftMask,                    XK_Print,          spawn,          CMD("maim -i $(xdotool getactivewindow) ~/ss/$(date +%d%h%T).png") },
	{ ControlMask,                  XK_Print,          spawn,          CMD("maim -s ~/ss/$(date +%d%h%T).png") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
