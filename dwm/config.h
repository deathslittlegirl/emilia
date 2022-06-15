/* see LICENSE file for copyright and license details. */

/* it compiles faster like this */

#include "tatami.c"
#include <X11/XF86keysym.h>

/* key definitions */

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* it does not compile faster like that hahaha */

/* appearance */

static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { "terminus:size=9" };
static const char dmenufont[]       = "terminus:size=9";

/* background color */

static const char col_gray1[]       = "#1e1c1c";

/* inactive window border color */

static const char col_gray2[]       = "#000000";

/* font color */

static const char col_gray3[]       = "#ffffff";

/* current tag and current window font color */

static const char col_gray4[]       = "#ffffff";

/* top bar second color and active window border color */

static const char col_cyan[]        = "#f22777";

/* commit to velvet later */

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
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       0,       	    0,           -1 },
	{ "Renoise",  NULL,	  NULL,	      0,	    0,		 -1 },
	{ "broken",   NULL,	  NULL,		1 >> 8,		0,	0 }, 
};

/* layout(s) */

static const float mfact     = 0.66; /* factor of master area size [0.05..0.95] */

static const int nmaster     = 1;    /* number of clients in master area */

static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
								/*

 	symbol     	arrangement 				

								*/	
	{ "|+|",      	tatami },    /* first entry is default */
	{ "><>",      	NULL },    /* no layout function means floating behavior */
	{ "[M]",      	monocle },
	{ "[]=",	tile },

};

/* dmenu */

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

/* system control */

static const char *termcmd[]  = { "alacritty", NULL };
static const char *rofi[] = { "rofi", "-show", "drun", NULL };

static const char *upmica[] = { "amixer", "set", "-c", "2", "Capture", "2+", NULL };
static const char *downmica[] = { "amixer", "set", "-c", "2", "Capture", "2-", NULL };

static const char *upmicb[] = { "amixer", "set", "-c", "2", "Capture", "6+", NULL }; 
static const char *downmicb[] = { "amixer", "set", "-c", "2", "Capture", "6-", NULL }; 

static const char *mutemic[] = { "amixer", "set", "-c", "2", "Capture", "toggle", NULL }; 

static const char *upvol[] = { "amixer", "set", "-c", "2", "Master", "2+",  NULL };
static const char *downvol[] = { "amixer", "set", "-c", "2", "Master", "2-", NULL };

static const char *mutevol[] = { "amixer", "set", "-c", "2", "Master", "toggle", NULL };

static const char *screenup[] = { "light", "-A", "10", NULL };
static const char *screendown[] = { "light", "-U", "10", NULL };

static const char *kbdup[] = { "light", "-s", "sysfs/leds/asus::kbd_backlight", "-A", "50",  NULL };
static const char *kbddown[] = { "light", "-s", "sysfs/leds/asus::kbd_backlight", "-U", "50",  NULL };

static const char *dwmcon1[] = { "alacritty", "-e", "vim", "/home/neko/Downloads/sorc/dwm/config.h", NULL };
static const char *dwmcon2[] = { "alacritty", "-e", "vim", "/home/neko/.dwm/autostart.sh", NULL };

static const char *sctrl1[] = { "alacritty", "-e", "alsamixer", NULL };
static const char *sctrl2[] = { "pavucontrol", NULL };

/* utility */

static const char *wp[] = { "nitrogen", NULL };

static const char *ss[] = { "scrot", "-s", NULL };
static const char *ssf[] = { "scrot", "-f", NULL };
static const char *sr[] = { "simplescreenrecorder", NULL };

static const char *fm1[] = { "nemo", NULL };
static const char *fm2[] = { "alacritty", "-e", "mc", "-b", NULL };

static const char *pwmgr[] = { "keepassxc", NULL };

static const char *emoji[] = { "gnome-characters", NULL };
static const char *sysmon[] = { "alacritty", "-e", "htop", NULL };

/* general applications */

static const char *e1[] = { "alacritty", "-e", "vim", NULL };
static const char *e2[] =  { "emacs", NULL };
static const char *e3[] = { "gnome-text-editor", NULL };

/* web */

static const char *msg1[] = { "Discord", NULL };
static const char *msg2[] = { "alacritty", "-e", "weechat", NULL };

static const char *brw1[] = { "firefox", NULL };
static const char *brw2[] = { "vivaldi", NULL }; 

static const char *prn1[] = { "firefox", "https://xvideos.com", NULL };
static const char *prn2[] = { "firefox", "https://chan.sankakucomplex.com/", NULL };

static const char *github[] = { "io.github.shiftey.Desktop", NULL };


/* photo */

static const char *pe[] = { "gimp", "-n", "-a",  NULL };
static const char *pv[] = { "nomacs", NULL }; 
static const char *c[] = { "org.kde.kcolorchooser", NULL };

/* video */

static const char *ve[] = { "kdenlive", NULL };
static const char *vv[] = { "vlc", NULL };

/* audio */

static const char *daw1[] = { "bitwig-studio", NULL };
static const char *daw2[] = { "renoise", NULL };

static const char *m1[] = { "com.spotify.Client", NULL };
static const char *m2[] = { "io.freetubeapp.FreeTube", NULL };
static const char *m3[] = { "alacritty", "-e", "cmus", NULL };

static const char *radio1[] = { "goodvibes", NULL };
static const char *radio2[] = { "de.haeckerfelix.Shortwave", NULL };

/* gaming */

static const char *steam[] = { "steam", NULL };
/*static const char *lutris[] = { "lutris", NULL };*/
static const char *game1[] = { "./home/neko/.steam/steam/steamapps/common/Terraria/Terraria", NULL };
static const char *game2[] = { "./home/neko/.steam/steam/steamapps/common/tModLoader/tModLoader", NULL }; 
/* commands */

static Key keys[] = {

	/* modifier             key     	function     	argument */

	/* access configuration */

	{ MODKEY|ShiftMask,	XK_bracketright,	spawn,	{ .v = dwmcon1 } },
	{ MODKEY|ShiftMask,	XK_bracketleft,		spawn,	{ .v = dwmcon2 } },


	/* utility */

	{ MODKEY,		XK_F2,		spawn,		{ .v = sysmon } },

	{ MODKEY,		XK_F1,		spawn,  	{ .v = dmenucmd } },		
	{ Mod1Mask,		XK_F1,		spawn,  	{ .v = dmenucmd } },		
	{ Mod1Mask,		XK_p,		spawn,		{ .v = dmenucmd } },

	{ MODKEY|ShiftMask,	XK_Return, 	spawn, 		{ .v = termcmd } },
	{ Mod1Mask|ShiftMask,	XK_Return, 	spawn, 		{ .v = termcmd } },
		
	{ Mod1Mask,		XK_Tab, 	spawn, 		{ .v = termcmd } },
	
	{ Mod1Mask|ShiftMask,	XK_Tab,		spawn,  	{ .v = rofi } },
	
	{ ShiftMask,		XK_Print,	spawn,		{ .v = ssf } },
	{ 0,			XK_Print,	spawn,		{ .v = ss } },	
	{ MODKEY,		XK_Print,	spawn,		{ .v = sr } },
	
	{ ControlMask,		XK_Escape,	spawn,		{ .v = pwmgr } },	

	{ MODKEY|ShiftMask,	XK_f,		spawn,		{ .v = fm1 } },
	{ MODKEY|ControlMask, 	XK_f, 		spawn,  	{ .v = fm2 } },
	
	{ MODKEY,		XK_e,		spawn,		{ .v = e1 } },	
	{ MODKEY|ShiftMask, 	XK_e, 		spawn,    	{ .v = e2 } },
	{ MODKEY|ControlMask,	XK_e,		spawn,		{ .v = e3 } },

	{ MODKEY,		XK_grave,	spawn,		{ .v = emoji } },

	/* system control */
	
	{ 0,	XF86XK_MonBrightnessUp,		spawn,		{ .v = screenup } },
	{ 0,	XF86XK_MonBrightnessDown, 	spawn,		{ .v = screendown } },
	
	{ MODKEY,         XK_F4,		spawn,		{ .v = screenup } },	
	{ MODKEY,         XK_F3,		spawn,		{ .v = screendown } },
	
	{ 0,	XF86XK_KbdBrightnessUp,		spawn,		{ .v = kbdup } },
	{ 0,	XF86XK_KbdBrightnessDown,	spawn,		{ .v = kbddown } },
	
	{ MODKEY,	XF86XK_AudioMute,	spawn,		{ .v = mutemic } },
	{ MODKEY,	XK_Escape,		spawn,		{ .v = mutemic } },

	{ MODKEY,	XF86XK_AudioRaiseVolume, spawn,		{ .v = upmica } },
	{ MODKEY,	XF86XK_AudioLowerVolume, spawn,		{ .v = downmica } },

	{ MODKEY|ShiftMask,	XF86XK_AudioRaiseVolume, spawn,	{ .v = upmicb } },
	{ MODKEY|ShiftMask,	XF86XK_AudioLowerVolume, spawn,	{ .v = downmicb } },
		
	{ 0,	XF86XK_AudioRaiseVolume,	spawn,		{ .v = upvol } },
	{ 0,	XF86XK_AudioLowerVolume,	spawn,		{ .v = downvol} },

	{ 0,	XF86XK_AudioMute,		spawn,		{ .v = mutevol } }, 
	
	/* quit */

	{ ControlMask|Mod1Mask,   XK_Delete,      quit,           {0} },
	{ MODKEY,		  XK_Delete,	  quit,		  {0} },
	{ ControlMask|MODKEY,	  XK_Delete,	  quit,		  {0} },
	{ MODKEY,		  XK_End,	  quit,		  {0} },
	
	/* web */

	{ MODKEY|ShiftMask,	XK_i,		spawn,		{ .v = msg1 } },
	{ MODKEY|ControlMask,	XK_i,		spawn,		{ .v = msg2 } },

	{ MODKEY,		XK_w,		spawn,		{ .v = brw1 } },
	{ MODKEY|ShiftMask,	XK_w,		spawn,		{ .v = brw2 } },

	{ Mod1Mask,		XK_w,		spawn,		{ .v = prn1 } },
	{ ShiftMask|Mod1Mask,	XK_w,		spawn,		{ .v = prn2 } }, 
	
	{ MODKEY|ControlMask,	XK_w,		spawn,		{ .v = github } },
	

	/* audio */

	{ MODKEY|ShiftMask,	XK_m,		spawn,		{ .v = m1 } },
	{ MODKEY|ControlMask,	XK_m,		spawn,		{ .v = m2 } },
	{ Mod1Mask,		XK_m,		spawn,		{ .v = m3 } },
	
	{ MODKEY,		XK_r,		spawn,		{ .v = radio1 } },
	{ MODKEY|ShiftMask,	XK_r,		spawn,		{ .v = radio2 } },
	
	{ Mod1Mask,		XK_d,		spawn,		{ .v = daw1 } },
	{ ControlMask|Mod1Mask,	XK_d,		spawn,		{ .v = daw2 } },

	{ MODKEY|ControlMask,	XK_s,		spawn,		{ .v = sctrl1 } },
	{ MODKEY|ShiftMask,	XK_s,		spawn,		{ .v = sctrl2 } },
	
	/* photo */

	
	{ MODKEY,		XK_p,		spawn,		{ .v = pv } },
	{ MODKEY,		XK_c,		spawn,		{ .v = c } },
	{ MODKEY|ShiftMask,	XK_p,		spawn,		{ .v = pe } },
	
	{ MODKEY|ShiftMask,	XK_n,		spawn,		{ .v = wp } },

	/* video */

	{ MODKEY,		XK_v,		spawn,		{ .v = vv } },	
	{ MODKEY|ShiftMask,	XK_v,		spawn,		{ .v = ve } },

	/* gaming */
	
	{ MODKEY,		XK_g,		spawn,		{ .v = steam } },
	{ MODKEY|ShiftMask,	XK_g,		spawn,		{ .v = game1 } },
	{ MODKEY|ControlMask,	XK_g,		spawn,		{ .v = game2 } },	


	/* layouts, focus, etc. */

	{ MODKEY,               XK_b,      	togglebar,      { 0 } },
	
	{ MODKEY,               XK_j,      	focusstack,     { .i = +1 } },
	{ MODKEY,               XK_k,      	focusstack,     { .i = -2 } },
	{ MODKEY,               XK_Up,      	focusstack,     { .i = +1 } },
	{ MODKEY,               XK_Down,      	focusstack,     { .i = -2 } },
	
	{ MODKEY,               XK_i,      	incnmaster,     { .i = +1 } },
	{ MODKEY,               XK_d,      	incnmaster,     { .i = -1 } },
	
	{ MODKEY,               XK_h,      	setmfact,       { .f = -0.03 } },
	{ MODKEY,               XK_l,      	setmfact,       { .f = +0.03 } },
	
	{ MODKEY,               XK_Return, 	zoom,           { 0 } },
	{ MODKEY,               XK_Tab,    	view,           { 0 } },
	{ MODKEY|ShiftMask,     XK_q,      	killclient,     { 0 } },
	
	{ MODKEY,               XK_t,      	setlayout,      { .v = &layouts[0] } },
	{ MODKEY,               XK_f,      	setlayout,      { .v = &layouts[1] } },
	{ MODKEY,               XK_m,      	setlayout,      { .v = &layouts[2] } },
	{ MODKEY,               XK_y,      	setlayout,      { .v = &layouts[3]} },
	
	{ MODKEY|ShiftMask,     XK_space,  	togglefloating, { 0 } },
	{ MODKEY,               XK_space,  	setlayout,      { 0 } },
	
	{ MODKEY,               XK_0,      	view,           { .ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,      	tag,           	{ .ui = ~0 } },
	
	{ MODKEY,               XK_comma,  	focusmon,      	{ .i = -1 } },
	{ MODKEY,               XK_period, 	focusmon,      	{ .i = +1 } },
	{ MODKEY,               XK_Left,  	focusmon,      	{ .i = -1 } },
	{ MODKEY,               XK_Right, 	focusmon,      	{ .i = +1 } },
	
	{ MODKEY|ShiftMask,     XK_comma,  	tagmon,        	{ .i = -1 } },
	{ MODKEY|ShiftMask,     XK_period, 	tagmon,         { .i = +1 } },
	{ MODKEY|ShiftMask,     XK_Left,  	tagmon,        	{ .i = -1 } },
	{ MODKEY|ShiftMask,     XK_Right, 	tagmon,         { .i = +1 } },
	

	/* workspaces */
	
	TAGKEYS(                XK_1,                      	0)
	TAGKEYS(                XK_2,                      	1)
	TAGKEYS(                XK_3,                      	2)
	TAGKEYS(                XK_4,                      	3)
	TAGKEYS(                XK_5,                      	4)
	TAGKEYS(                XK_6,                      	5)
	TAGKEYS(                XK_7,                      	6)
	TAGKEYS(                XK_8,                      	7)
	TAGKEYS(                XK_9,                      	8)



};


/* button definitions */

/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */

static Button buttons[] = {
	
	/* click                event mask      button          function        argument */
	
	{ ClkLtSymbol,          0,              Button1,        setlayout,      { 0 } },

	{ ClkLtSymbol,          0,              Button3,        setlayout,      { .v = &layouts[2]} },

	{ ClkWinTitle,          0,              Button2,        zoom,           { 0 } },
	{ ClkTagBar,            0,              Button1,        view,           { 0 } },
	{ ClkTagBar,            0,              Button3,        toggleview,     { 0 } },
	
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, { 0 } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      { 0 } },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    { 0 } },

	{ ClkStatusText,        0,              Button2,        spawn,          { .v = termcmd } },

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

/*jacktop*/
