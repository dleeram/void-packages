/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
	"bitmap:pixelsize=14"
};
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance    title       tags mask     isfloating   monitor */
	{ "qutebrowser",  NULL,       NULL,       1 << 1,       0,           -1 },
	{ "mpv",          NULL,       NULL,       0,            1,           -1 },
	{ "Sxiv",         NULL,       NULL,       0,            1,           -1 },
	{ "MuPDF",        NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define XF86XK_AudioMute         0x1008FF12
#define XF86XK_AudioLowerVolume  0x1008FF11
#define XF86XK_AudioRaiseVolume  0x1008FF13
#define XF86XK_AudioPrev         0x1008FF16
#define XF86XK_AudioPlay         0x1008FF14
#define XF86XK_AudioNext         0x1008FF17
#define XF86XK_MonBrightnessDown 0x1008FF03
#define XF86XK_MonBrightnessUp   0x1008FF02

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "dmenu_run", "-p", "run", NULL };
static const char *termcmd[]     = { "st", NULL };
static const char *vol_toggle[]  = { "amixer", "-q", "set", "Master", "toggle",  NULL };
static const char *vol_down[]    = { "amixer", "-q", "set", "Master", "5%-", "unmute",  NULL };
static const char *vol_up[]      = { "amixer", "-q", "set", "Master", "5%+", "unmute",  NULL };
static const char *song_prev[]   = { "mpc", "-q", "prev", NULL };
static const char *song_toggle[] = { "mpc", "-q", "toggle", NULL };
static const char *song_next[]   = { "mpc", "-q", "next", NULL };
static const char *bright_down[] = { "light", "-U", "5%", NULL };
static const char *bright_up[]   = { "light", "-A", "5%", NULL };

static Key keys[] = {
	/* modifier         key                       function        argument */
	{ MODKEY,           XK_p,                     spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask, XK_Return,                spawn,          {.v = termcmd } },
	{ 0,                XF86XK_AudioMute,         spawn,          {.v = vol_toggle } },
	{ 0,                XF86XK_AudioLowerVolume,  spawn,          {.v = vol_down } },
	{ 0,                XF86XK_AudioRaiseVolume,  spawn,          {.v = vol_up } },
	{ 0,                XF86XK_AudioPrev,         spawn,          {.v = song_prev } },
	{ 0,                XF86XK_AudioPlay,         spawn,          {.v = song_toggle } },
	{ 0,                XF86XK_AudioNext,         spawn,          {.v = song_next } },
	{ 0,                XF86XK_MonBrightnessDown, spawn,          {.v = bright_down } },
	{ 0,                XF86XK_MonBrightnessUp,   spawn,          {.v = bright_up } },
	{ MODKEY,           XK_b,                     togglebar,      {0} },
	{ MODKEY,           XK_j,                     focusstack,     {.i = +1 } },
	{ MODKEY,           XK_k,                     focusstack,     {.i = -1 } },
	{ MODKEY,           XK_i,                     incnmaster,     {.i = +1 } },
	{ MODKEY,           XK_d,                     incnmaster,     {.i = -1 } },
	{ MODKEY,           XK_h,                     setmfact,       {.f = -0.05} },
	{ MODKEY,           XK_l,                     setmfact,       {.f = +0.05} },
	{ MODKEY,           XK_Return,                zoom,           {0} },
	{ MODKEY,           XK_Tab,                   view,           {0} },
	{ MODKEY|ShiftMask, XK_c,                     killclient,     {0} },
	{ MODKEY,           XK_t,                     setlayout,      {.v = &layouts[0]} },
	{ MODKEY,           XK_f,                     setlayout,      {.v = &layouts[1]} },
	{ MODKEY,           XK_m,                     setlayout,      {.v = &layouts[2]} },
	{ MODKEY,           XK_space,                 setlayout,      {0} },
	{ MODKEY|ShiftMask, XK_space,                 togglefloating, {0} },
	{ MODKEY,           XK_0,                     view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask, XK_0,                     tag,            {.ui = ~0 } },
	{ MODKEY,           XK_comma,                 focusmon,       {.i = -1 } },
	{ MODKEY,           XK_period,                focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask, XK_comma,                 tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask, XK_period,                tagmon,         {.i = +1 } },
	TAGKEYS(            XK_1,                                     0)
	TAGKEYS(            XK_2,                                     1)
	TAGKEYS(            XK_3,                                     2)
	TAGKEYS(            XK_4,                                     3)
	TAGKEYS(            XK_5,                                     4)
	{ MODKEY|ShiftMask, XK_q,                     quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         Mod1Mask,       Button1,        resizemouse,    {0} },
};
