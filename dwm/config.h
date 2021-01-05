/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */

static const unsigned int gappih    = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;       /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */

static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Fira Code:size=12" };
static const char dmenufont[]       = "Fira Code:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";

static const char col_cyan[]        = "#005577";
static const char col_yellow[]      = "#d79921";
static const char col_green[]       = "#689d6a";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2   },
	[SchemeSel]  = { col_gray4, col_green, col_yellow  },
};

/* tagging */
static const char *tags[] = { "∫", "∇", "δ", "∂", "∆", "∑", "ℒ","ℑ", "ℵ"};  
// Ω

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	// { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 }, // tag 8
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1
#include "patches/vanitygaps.c"
// #include "patches/fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
 	{ "[M]",      monocle },
	// { "[@]",      spiral },
	// { "[\\]",     dwindle },
	// { "H[]",      deck },
	// { "TTT",      bstack },
	// { "===",      bstackhoriz },
	{ "HHH",      grid },
	// { "###",      nrowgrid },
	// { "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	// { ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include "patches/shiftview.c"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = { "rofi", "-show", NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static const char *upvolcmd[]   = { "pulseaudio-ctl", "up",   "3", NULL };
static const char *downvolcmd[] = { "pulseaudio-ctl", "down", "3", NULL };
static const char *mutevolcmd[] = { "pulseaudio-ctl", "mute",      NULL };

static const char *screenup[]   = { "xbacklight", "+5", NULL };
static const char *screendown[] = { "xbacklight", "-5", NULL };
static const char *kbdup[]      = { "/home/matt/scripts/kbdup",   NULL };
static const char *kbddown[]    = { "/home/matt/scripts/kbddown", NULL };
// static const char *kbdup[]      = { "brightnessctl", "--device='tpacpi::kbd_backlight'", "set", "1+", NULL };
// static const char *kbddown[]    = { "brightnessctl", "--device='tpacpi::kbd_backlight'", "set", "1-", NULL };
static const char *stats[]      = { "/home/matt/scripts/stats", NULL };

/* launching application commands */
static const char *spawndiscord[]  = { "discord", NULL };
static const char *spawnbrave[]    = { "browser", NULL };
static const char *spawnfirefox[]  = { "firefox", NULL };
static const char *spawnwolfram[]  = { "firefox", "https://wolframalpha.com", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } }, /* rotate clients */
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} }, // TEST
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } }, /* view all tags */
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },

    /* cyclelayout */
	{ MODKEY|ControlMask|ShiftMask, XK_space,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_space,  cyclelayout,    {.i = +1 } },

    /* shiftview */
	{ ControlMask|Mod1Mask,         XK_l,      shiftview,      {.i = +1 } },
	{ ControlMask|Mod1Mask,         XK_h,      shiftview,      {.i = -1 } },

    /* vanity gaps */
	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } }, // all
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	// { MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } }, // inner
	// { MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	// { MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } }, // outer
	// { MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	// { MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } }, // inner horiz
	// { MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	// { MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } }, // inner vert
	// { MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	// { MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } }, // outer horiz
	// { MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	// { MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } }, // outer vert
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
    
    /* fullscr */
	{ MODKEY,                       XK_m,      togglefullscr,  {0} },

    /* volume control */
	// { MODKEY,                       XK_F10,    spawn,          {.v = mutevolcmd } },
	{ MODKEY,                       XK_F2,    spawn,          {.v = downvolcmd } },
	{ MODKEY,                       XK_F3,    spawn,          {.v = upvolcmd   } },

    /* screen brightness */
	{ MODKEY,                       XK_F5,    spawn,          {.v = screendown } },
	{ MODKEY,                       XK_F6,    spawn,          {.v = screenup   } },

    /* keyboard brightness */
	{ MODKEY|ShiftMask,             XK_F5,    spawn,          {.v = kbddown } },
	{ MODKEY|ShiftMask,             XK_F6,    spawn,          {.v = kbdup   } },

    /* brightness stats */
	{ MODKEY,                       XK_F7,    spawn,          {.v = stats } },

    /* launching programs */
	{ MODKEY,                       XK_d,      spawn,         {.v = spawndiscord } },
	{ MODKEY,                       XK_f,      spawn,         {.v = spawnfirefox } },
	// { MODKEY,                       XK_f,      spawn,         {.v = spawnbrave   } },
	{ MODKEY,                       XK_w,      spawn,         {.v = spawnwolfram } },

    /* change monitors */

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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

