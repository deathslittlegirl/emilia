/* See LICENSE file for copyright and license details. */

/* appearance */

static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { "terminus:size=10" };
static const char dmenufont[]       = "terminus:size=10";

/*Background color*/

static const char col_gray1[]       = "#000000";

/*Inactive window border color*/

static const char col_gray2[]       = "#000000";

/*Font color*/

static const char col_gray3[]       = "#ffffff";

/*Current tag and current window font color*/

static const char col_gray4[]       = "#ffffff";

/*Top bar second color and active window border color*/

static const char col_cyan[]        = "#224488";


static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
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
	{ "Renoise",	NULL,	NULL,	1 << 8,	1,	-1 },
};

/* layout(s) */

static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */

static const int nmaster     = 1;    /* number of clients in master area */

static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

/*tatami tiem*/

#include "tatami.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "|+|",      tatami },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[]=",	tile },
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

/* Dmenu */

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

/* Utility */

static const char *termcmd[]  = { "alacritty", NULL };
static const char *rofi[] = { "rofi", "-show", "drun", NULL };
static const char *scrot[] = { "scrot", "-s", NULL };
static const char *scrotf[] = {"scrot", "-f", NULL };

static const char *fm[] = { "nemo", NULL };
static const char *fm2[] = { "alacritty", "-e", "mc" };

static const char *kpxc[] = { "keepassxc", NULL };
static const char *color[] = { "org.kde.kcolorchooser", NULL };
static const char *emoji[] = { "gnome-characters", NULL };

/* Applications */

static const char *e[] = { "alacritty", "-e", "vim", NULL };
static const char *e2[] =  { "emacs", NULL };

static const char *m[] = { "com.spotify.Client", NULL };
static const char *m2[] = { "io.freetubeapp.FreeTube", NULL };
static const char *m3[] = { "alacritty", "-e", "cmus", NULL };

static const char *radio[] = { "de.haeckerfelix.Shortwave", NULL };
static const char *nitrogen[] = { "nitrogen", NULL };
static const char *msger[] = { "Discord", NULL };

static const char *b[] = { "firefox", NULL };
static const char *b2[] = { "vimb", NULL }; 
static const char *xvideos[] = { "firefox", "https://xvideos.com", NULL };
static const char *sankaku[] = { "firefox", "https://chan.sankakucomplex.com/", NULL };


/* Sound */

static const char *mutemic[] = { "amixer", "set", "-c", "2", "Capture", "toggle" }; 

static const char *upmica[] = { "amixer", "set", "-c", "2", "Capture", "3+", NULL };
static const char *downmica[] = { "amixer", "set", "-c", "2", "Capture", "3-", NULL };

static const char *upmicb[] = { "amixer", "set", "-c", "2", "Capture", "6+", NULL }; 
static const char *downmicb[] = { "amixer", "set", "-c", "2", "Capture", "6-", NULL }; 

static const char *upvol[] = { "amixer", "set", "-c", "2", "Master", "2+",  NULL };
static const char *downvol[] = { "amixer", "set", "-c", "2", "Master", "2-", NULL };
static const char *mutevol[] = { "amixer", "set", "-c", "2", "Master", "toggle", NULL };
static const char *amixer[] = { "alacritty", "-e", "alsamixer", NULL };
static const char *pavu[] = { "pavucontrol", NULL };
static const char *daw[] = { "bitwig-studio", NULL };
static const char *daw2[] = { "renoise", NULL };


/* Backlight */

static const char *screenup[] = { "light", "-A", "10", NULL };
static const char *screendown[] = {"light", "-U", "10", NULL };

static const char *kbdup[] = { "light", "-s", "sysfs/leds/asus::kbd_backlight", "-A", "50",  NULL };
static const char *kbddown[] = { "light", "-s", "sysfs/leds/asus::kbd_backlight", "-U", "50",  NULL };

/* Commands */

#include <X11/XF86keysym.h>

static Key keys[] = {

	/* modifier             key     	function     	argument */
	
	/* Utility */
	
	{ MODKEY,		XK_Escape,	spawn,  	{ .v = dmenucmd } },
	{ MODKEY|ShiftMask,     XK_Return, 	spawn, 		{ .v = termcmd } },
	
	{ MODKEY,		XK_F8,		spawn,		{ .v = screenup } },	
	{ MODKEY,		XK_F7,		spawn,		{ .v = screendown } },
	{ 0,	XF86XK_MonBrightnessUp,		spawn,		{ .v = screenup } },
	{ 0,	XF86XK_MonBrightnessDown, 	spawn,		{ .v = screendown } },

	{ MODKEY,		XK_q,		spawn,  	{ .v = rofi } },
	{ 0,			XK_Print,	spawn,		{ .v = scrot } },
	{ ShiftMask,		XK_Print,	spawn,		{ .v = scrotf } },
	
	{ MODKEY|ShiftMask,	XK_n,		spawn,		{ .v = nitrogen } },
	{ MODKEY,		XK_p,		spawn,		{ .v = kpxc } },	
	{ MODKEY,		XK_c,		spawn,		{ .v = color } },

	{ 0,	XF86XK_KbdBrightnessUp,		spawn,		{ .v = kbdup } },
	{ 0,	XF86XK_KbdBrightnessDown,	spawn,		{ .v = kbddown } },
	
	{ MODKEY,		XK_x,		spawn,		{ .v = xvideos } },
	{ MODKEY|ShiftMask,	XK_x,		spawn,		{ .v = sankaku } }, 
	
	{ MODKEY|ControlMask,	XK_e,		spawn,		{ .v = emoji } },
	/* Volume/Sound-Related */
	
	{ MODKEY,   		XK_a, 		spawn,  	{.v = mutemic } },

	{ 0,	XF86XK_AudioRaiseVolume,	spawn,		{ .v = upvol } },
	{ 0,	XF86XK_AudioLowerVolume,	spawn,		{ .v = downvol} },
	{ 0,	XF86XK_AudioMute,		spawn,		{ .v = mutevol } }, 
	
	{ MODKEY,	XF86XK_AudioRaiseVolume, spawn,		{ .v = upmica } },
	{ MODKEY,	XF86XK_AudioLowerVolume, spawn,		{ .v = downmica } },

	{ MODKEY|ShiftMask,	XF86XK_AudioRaiseVolume, spawn,	{ .v = upmicb } },
	{ MODKEY|ShiftMask,	XF86XK_AudioLowerVolume, spawn,	{ .v = downmicb } },
	
	
	{ MODKEY|ControlMask,	XK_s,		spawn,		{ .v = amixer } },
	{ MODKEY|ShiftMask,	XK_s,		spawn,		{ .v = pavu } },
	{ MODKEY|ShiftMask,	XK_m,		spawn,		{ .v = m } },
	{ MODKEY|ControlMask,	XK_m,		spawn,		{ .v = m2 } },
	{ MODKEY|ControlMask|ShiftMask,	XK_m,	spawn,		{ .v = m3 } },
	{ MODKEY|Mod1Mask,	XK_m,		spawn,		{ .v = radio } },
	
	{ MODKEY,		XK_d,		spawn,		{ .v = daw } },
	{ MODKEY|Mod1Mask,	XK_d,		spawn,		{ .v = daw2 } },
	
	/* General Applications */
	
	
	{ MODKEY,		XK_i,		spawn,		{ .v = msger } },
	{ MODKEY,		XK_w,		spawn,		{ .v = b } },
	{ MODKEY|ShiftMask,	XK_w,		spawn,		{ .v = b2 } },
	

	{ MODKEY|ShiftMask,	XK_f,		spawn,		{ .v = fm } },
	{ MODKEY|ControlMask, 	XK_f, 		spawn,  	{ .v = fm2 } },
	
	{ MODKEY,		XK_e,		spawn,		{ .v = e } },	
	{ MODKEY|ShiftMask, 	XK_e, 		spawn,    	{ .v = e2 } },

	/* Layouts, focus, etc. */
	{ MODKEY,               XK_b,      	togglebar,      { 0 } },
	{ MODKEY,               XK_j,      	focusstack,     { .i = +1 } },
	{ MODKEY,               XK_k,      	focusstack,     { .i = -2 } },
	{ MODKEY,               XK_i,      	incnmaster,     { .i = +1 } },
	{ MODKEY,               XK_d,      	incnmaster,     { .i = -1 } },
	{ MODKEY,               XK_h,      	setmfact,       { .f = -0.05} },
	{ MODKEY,               XK_l,      	setmfact,       { .f = +0.05} },
	{ MODKEY,               XK_Return, 	zoom,           { 0 } },
	{ MODKEY,               XK_Tab,    	view,           { 0 } },
	{ MODKEY|ShiftMask,     XK_q,      	killclient,     { 0 } },
	{ MODKEY,               XK_t,      	setlayout,      { .v = &layouts[0]} },
	{ MODKEY,               XK_f,      	setlayout,      { .v = &layouts[1]} },
	{ MODKEY,               XK_m,      	setlayout,      { .v = &layouts[2]} },
	{ MODKEY,               XK_y,      	setlayout,      { .v = &layouts[3]} },
	{ MODKEY,               XK_space,  	setlayout,      { 0 } },
	{ MODKEY|ShiftMask,     XK_space,  	togglefloating, { 0 } },
	{ MODKEY,               XK_0,      	view,           { .ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,      	tag,           	{ .ui = ~0 } },
	{ MODKEY,               XK_comma,  	focusmon,      	{ .i = -1 } },
	{ MODKEY,               XK_period, 	focusmon,      	{ .i = +1 } },
	{ MODKEY|ShiftMask,     XK_comma,  	tagmon,        	{ .i = -1 } },
	{ MODKEY|ShiftMask,     XK_period, 	tagmon,         { .i = +1 } },
	 	
	/* Workspaces */
	TAGKEYS(                XK_1,                      	0)
	TAGKEYS(                XK_2,                      	1)
	TAGKEYS(                XK_3,                      	2)
	TAGKEYS(                XK_4,                      	3)
	TAGKEYS(                XK_5,                      	4)
	TAGKEYS(                XK_6,                      	5)
	TAGKEYS(                XK_7,                      	6)
	TAGKEYS(                XK_8,                      	7)
	TAGKEYS(                XK_9,                      	8)
	{ MODKEY|ControlMask,   XK_Delete,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      { 0 } },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      { .v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           { 0 } },
	{ ClkStatusText,        0,              Button2,        spawn,          { .v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      { 0 } },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, { 0 } },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    { 0 } },
	{ ClkTagBar,            0,              Button1,        view,           { 0 } },
	{ ClkTagBar,            0,              Button3,        toggleview,     { 0 } },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            { 0 } },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      { 0 } },
};
void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
};

/*jacktop online*/
