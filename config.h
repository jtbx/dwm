/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 10; 	/* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = { "JetBrainsMono-Regular:size=12" };
static const char dmenufont[]       = "JetBrainsMono-Regular:size=10";
static const char col_gray1[]       = "#121212";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
/* was #eeeeee */
/* col_accent used to be #2644ba */
static const char col_gray4[]       = "#ffffff";
static const char col_accent[]        = "#005faf";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_accent,  col_accent  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "LibreWolf", NULL,    NULL,          0,         0,          0,           0,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "Alacritty", NULL,   NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[=]",      tile },    /* first entry is default */
	{ "<->",      NULL },    /* no layout function means floating behavior */
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
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* Dmenu command remapped to rofi */
static const char *dmenucmd[] = { "dmenu_run", NULL };
/* Rofi application menu variable so it can be spawned using mod + x */ 
static const char *appmenucmd[] = { "rofi", "-show", "drun", NULL };
/* Terminal command remapped to alacritty */
static const char *termcmd[]  = { "alacritty", NULL };
/* Web browser variable so it can be spawned using mod + e */
static const char *wbrsrcmd[] = { "librewolf", NULL };
 /* Rofi emoji menu variable so it can be spawned using mod + period */
/* requires rofi-emoji                                              */
static const char *emojicmd[] = { "rofi", "-show", "emoji", NULL };
/* Power off variable so it can be run using mod + shift + escape */
static const char *powercmd[] = { "poweroff", NULL };
/* Reboot variable so it can be run using mod + shift + r */
static const char *rebootcmd[] = { "reboot", NULL };

/* For powercmd & rebootcmd I'm planning for it to open a terminal window where it would ask you to confirm the poweroff/reboot. */

static Key keys[] = {
	/* modifier                  key           function        argument */
	{ MODKEY,                    XK_d,         spawn,          {.v = dmenucmd } },
	{ MODKEY,                    XK_x,         spawn,          {.v = appmenucmd } },
	{ MODKEY,                    XK_Return,    spawn,          {.v = termcmd } },
	/* allows for spawning web browser */
	{ MODKEY,                    XK_w,         spawn,          {.v = wbrsrcmd } },
	/* allows for spawning emoji menu */
	{ MODKEY,                    XK_semicolon, spawn,          {.v = emojicmd } },
	/* allows for turning off computer */
	{ MODKEY|ShiftMask,          XK_Escape,    spawn,          {.v = powercmd } },
	/* allows for rebooting computer */
	{ MODKEY|ShiftMask,          XK_r,         spawn,          {.v = rebootcmd } },
	{ MODKEY,                    XK_b,         togglebar,      {0} },
	{ MODKEY,                    XK_j,         focusstack,     {.i = +1 } },
	{ MODKEY,                    XK_k,         focusstack,     {.i = -1 } },
	{ MODKEY,                    XK_i,         incnmaster,     {.i = +1 } },
	{ MODKEY,                    XK_d,         incnmaster,     {.i = -1 } },
	{ MODKEY,                    XK_h,         setmfact,       {.f = -0.05} },
	{ MODKEY,                    XK_l,         setmfact,       {.f = +0.05} },
	{ MODKEY,                    XK_Return,    zoom,           {0} },
	{ MODKEY,                    XK_Tab,       view,           {0} },
	{ MODKEY,                    XK_q,         killclient,     {0} },
	{ MODKEY,                    XK_t,         setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XK_f,         setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    XK_m,         setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                    XK_space,     setlayout,      {0} },
	{ MODKEY|ShiftMask,          XK_space,     togglefloating, {0} },
	{ MODKEY,                    XK_0,         view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,          XK_0,         tag,            {.ui = ~0 } },
	{ MODKEY,                    XK_comma,     focusmon,       {.i = -1 } },
	{ MODKEY,                    XK_period,    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,          XK_comma,     tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,          XK_period,    tagmon,         {.i = +1 } },
	{ MODKEY,                    XK_minus,     setgaps,        {.i = -1 } },
	{ MODKEY,                    XK_equal,     setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,          XK_equal,     setgaps,        {.i = 0  } },
	TAGKEYS(                     XK_1,                         0)
	TAGKEYS(                     XK_2,                         1)
	TAGKEYS(                     XK_3,                         2)
	TAGKEYS(                     XK_4,                         3)
	TAGKEYS(                     XK_5,                         4)
	TAGKEYS(                     XK_6,                         5)
	TAGKEYS(                     XK_7,                         6)
	TAGKEYS(                     XK_8,                         7)
	TAGKEYS(                     XK_9,                         8)
	{ MODKEY,                    XK_Escape,    quit,           {0} },
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

