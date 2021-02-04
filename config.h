/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 8;       /* gap pixel between windows */
static const unsigned int snap      = 15;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 5;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 21;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "Cascadia Code:size=10:style=Bold:dpi=96:antialias=true:hinting=true:hintstyle=hintslight:autohinting=false:lcdfilter=lcddefault", "JoyPixels:pixelsize=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "Cascadia Code:size=10:style=Bold:dpi=96:antialias=true:hinting=true:hintstyle=hintslight:autohinting=false:lcdfilter=lcddefault";
static const char col_gray1[]       = "#1b1e2b";
static const char col_gray2[]       = "#3c4261";
static const char col_gray3[]       = "#a8b4ff";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#ffb26b";
static const char col_blue[]        = "#548aff";
static const char col1[]            = "#f07178";
static const char col2[]            = "#719eff";
static const char col3[]            = "#c387ea";
static const char col4[]            = "#82dbff";
static const char col5[]            = "#b7e07c";
static const char col6[]            = "#ffb26b";

enum { SchemeNorm, SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
       SchemeCol5, SchemeCol6, SchemeStatus, SchemeTagsSel, SchemeTagsNorm, SchemeInfoSel, SchemeInfoNorm, SchemeSel }; /* color schemes */

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeCol1]  = { col_gray1,      col1, col_gray2 },
	[SchemeCol2]  = { col_gray1,      col2, col_gray2 },
	[SchemeCol3]  = { col_gray1,      col3, col_gray2 },
	[SchemeCol4]  = { col_gray1,      col4, col_gray2 },
	[SchemeCol5]  = { col_gray1,      col5, col_gray2 },
	[SchemeCol6]  = { col_gray1,      col6, col_gray2 },
	[SchemeStatus]  = { col_gray3, col_gray1,  col_gray2  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray1, col_blue,  col_gray2  }, // Tagbar left selected {text,background,not used but cannot be empty}
   [SchemeTagsNorm]  = { col_gray3, col_gray1,  col_gray2  }, // Tagbar left unselected {text,background,not used but cannot be empty}
   [SchemeInfoSel]  = { col_gray1, col5,  col_gray2  }, // infobar middle  selected {text,background,not used but cannot be empty}
   [SchemeInfoNorm]  = { col_gray3, col_gray1,  col_gray2  }, // infobar middle  unselected {text,background,not used but cannot be empty}
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
/* static const char *tags[] = { "dev", "www", "sys", "irc", "music", "vlc", "files", "stuff", "misc" }; */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Viewnior",  NULL,       NULL,       0,       	1,           -1 },	
	{ "vlc",  	NULL,       NULL,       0,       	1,           -1 },	
	{ "Audacious",  NULL,       NULL,       0,       	1,           -1 },	
	{ "Xfce4-appfinder",  NULL,       NULL,       0,       	1,           -1 },	
	{ "qt5ct",  NULL,       "Qt5 Configuration Tool",       0,       	1,           -1 },	
	{ "Lxappearance",  NULL,       NULL,       0,       	1,           -1 },	
	{ "Nitrogen",  NULL,       NULL,       0,       	1,           -1 },	
	{ "Deadbeef",  NULL,       NULL,       0,       	1,           -1 },	
	{ "feh",  NULL,       NULL,       0,       	1,           -1 },	
	{ "Sxiv",  NULL,       NULL,       0,       	1,           -1 },	


};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[tile]",      tile },    /* first entry is default */
	{ "[floating]",      NULL },    /* no layout function means floating behavior */
	{ "[monocle]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col3, "-sf", col_gray1, "-shb", col_gray1, "-shf", col3, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *jgmenucmd[]  = { "jgmenu_run", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             			XK_Return, spawn,          {.v = termcmd } },
	/* { MODKEY,             			XK_KP_Subtract, spawn,      SHCMD("amixer -D pulse sset Master 5%-") }, */
	{ MODKEY,             			XK_KP_Subtract, spawn,      SHCMD("amixer sset Master 5%-") },
	/* { MODKEY,             			XK_KP_Add, spawn,      		SHCMD("amixer -D pulse sset Master 5%+") }, */
	{ MODKEY,             			XK_KP_Add, spawn,      		SHCMD("amixer sset Master 5%+") },	
	{ MODKEY|ShiftMask,           XK_KP_Add, spawn,      SHCMD("pactl set-sink-volume 0 +5%") },
	{ MODKEY,             			XK_F1, spawn,      		SHCMD("chromium --force-dark-mode") },			
	{ MODKEY,             			XK_F2, spawn,      		SHCMD("code") },			
	/* { MODKEY,             			XK_F5, spawn,      		SHCMD("xfce4-appfinder") },	*/
	{ MODKEY|ShiftMask,             XK_Return, spawn,         SHCMD("thunar") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },	
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.025} },
	{ MODKEY,                       XK_semicolon,      setmfact,       {.f = +0.025} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,						XK_Tab,		shiftview,		{ .i = 1 } },
	{ MODKEY,             			XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
/*	{ ControlMask|ShiftMask,        XK_t,  		spawn,      SHCMD("st") },	*/
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
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
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 	
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        killclient,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,				0,					 Button3,		  spawn, {.v = jgmenucmd } },
	{ ClkRootWin,				0,					 Button3,		  spawn, {.v = jgmenucmd } },
};

