/* see LICENSE file for copyright and license details. */
/*stable on linux kernel 6.0.2-archlinux*/
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
static const int startwithgaps = 1;
static const unsigned int gappx = 20;
static const unsigned int snap      = 32;       /* snap pixel */


/* ok so like its just aesthetic sure but */


static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { "terminus:size=8" };
static const char dmenufont[]       = "terminus:size=8";


/* background color */

static const char col_gray1[]       = "#010101"; /* #292929 previously */

/* inactive window border color */

static const char col_gray2[]       = "#ffffff"; /* #8d9bfc previously */

/* font color */

static const char col_gray3[]       = "#01d181"; /* previously #01d181 */

/* current tag and current window font color */

static const char col_gray4[]       = "#a11113"; /* previously #ffffff */

/* top bar second color and active window border color */

static const char col_cyan[]        = "#01d181"; /*#f68bd4 previously*/

static const char *colors[][3]      = {

	/*               fg         bg         border   */

	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },

};

/* tagging */

static const char *tags[] = { "ª♀", "XI", "XII", "XIV" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       0,       	    0,           -1 },
	{ "Renoise",  NULL,	  NULL,	      0,	    0,		 -1 }, 
};

/* layout(s) */

static const float mfact     = 0.61; /* factor of master area size [0.05..0.95] */

static const int nmaster     = 1;    /* number of clients in master area */

static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
								/*

 	symbol     	arrangement 				

								*/	
	{ "ia",      	tatami },    /* first entry is default */
	{ "f",      	NULL },    /* no layout function means floating behavior */
	{ "m",      	monocle },
	{ "t",	        tile },
	{ "cm",         centeredmaster },
	{ "cm:f",       centeredfloatingmaster },
	};

/* dmenu */

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] = { "dmenu_run", "-b", "-p", "lia", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

/* system control */

static const char *termcmd[]  = { "alacritty", NULL};
static const char *termcmd2[]  = { "cool-retro-term", NULL};

static const char *rofi[] = { "rofi", "-show", "drun", NULL };

static const char *upmica[] = { "amixer", "set", "-c", "2", "Capture", "1+", NULL };
static const char *downmica[] = { "amixer", "set", "-c", "2", "Capture", "1-", NULL };

static const char *upmicb[] = { "amixer", "set", "-c", "3", "Mic", "1+", NULL }; 
static const char *downmicb[] = { "amixer", "set", "-c", "3", "Mic", "1-", NULL }; 

static const char *mutemic[] = { "amixer", "set", "-c", "2", "Capture", "toggle", NULL }; 

static const char *mutemicb[] = { "amixer", "set", "-c", "3", "Mic", "toggle", NULL }; 

static const char *killmicboost[] = { "amixer", "set", "-c", "2", "'Internal Mic Boost'", "0", NULL };

static const char *emiup[] = { "amixer", "set", "-c", "2", "Master", "2%+", NULL }; 
static const char *emidown[] = { "amixer", "set", "-c", "2", "Master", "2%-", NULL }; 

static const char *plystop[] = { "playerctl", "--all-players", "stop", NULL }; 
static const char *plyplay[] = { "playerctl", "--all-players", "play-pause", NULL }; 
static const char *plyback[] = { "playerctl", "position", "3-", NULL };
static const char *plyfore[] = { "playerctl", "position", "3+", NULL };
static const char *plyprev[] = { "playerctl", "previous", NULL};
static const char *plynext[] = { "playerctl", "next", NULL};
static const char *plyback2[] = { "playerctl", "position", "10-", NULL };
static const char *plyfore2[] = { "playerctl", "position", "10+", NULL };
static const char *plyloop[] = { "playerctl", "loop", "Track" }; 
static const char *plyloop2[] = { "playerctl", "loop", "Playlist" };
static const char *plyloop3[] = { "playerctl", "loop", "None" };
static const char *plyvolup[] = { "playerctl", "volume", "0.1+"};
static const char *plyvoldown[] = { "playerctl", "volume", "0.1-"};
static const char *mutevol[] = { "amixer", "set", "-c", "2", "Master", "toggle", NULL };

static const char *screenup[] = { "light", "-A", "10", NULL };
static const char *screendown[] = { "light", "-U", "10", NULL };

static const char *kbdup[] = { "light", "-s", "sysfs/leds/asus::kbd_backlight", "-A", "50",  NULL };
static const char *kbddown[] = { "light", "-s", "sysfs/leds/asus::kbd_backlight", "-U", "50",  NULL };

static const char *dwmcon1[] = { "alacritty", "-e", "emacs", "-nw", "~/.lia/config.h", NULL };
static const char *dwmcon2[] = { "alacritty", "-e", "emacs", "-nw", "~/.dwm/autostart.sh", NULL };

static const char *sctrl1[] = { "pavucontrol", "--tab=2", NULL };
static const char *sctrl2[] = { "cool-retro-term", "-e", "alsamixer", NULL };
static const char *sctrl3[] = { "org.rncbc.qpwgraph", NULL };

/* utility */

static const char *wp[] = { "nitrogen", NULL };

static const char *ss[] = { "scrot", "-s", "-q", "100", NULL };
static const char *ssf[] = { "scrot", "-f", "-q", "100", NULL };
static const char *sr[] = { "simplescreenrecorder", NULL };

static const char *fm1[] = { "pcmanfm-qt", NULL };
static const char *fm2[] = { "alacritty", "-e", "mc", "-b", NULL };

static const char *pwmgr[] = { "keepassxc", NULL };

static const char *emoji[] = { "gnome-characters", NULL };
static const char *sysmon[] = { "alacritty", "-e", "sudo", "htop", NULL };

static const char *transset[] = { "transset-df", NULL };

static const char *nicotine[] = { "org.nicotine_plus.Nicotine", NULL };

/* general applications */

static const char *editor[] = { "alacritty", "-e", "emacs", "-nw", NULL };
static const char *viewer[] =  { "evince", NULL };
static const char *mail[] = { "thunderbird", "-calendar", NULL }; 

/* web */

/* static const char *msg1[] = { "com.discordapp.Discord", "--ignore-gpu-blocklist", "--disable-features=UseOzonePlatform", "--enable-features=VaapiVideoDecoder", "--use-gl=desktop", "--enable-gpu-rasterization", "--enable-zero-copy", "--no-sandbox", "use-angle=vulkan", NULL }; */

static const char *msg1[] = { "com.discordapp.Discord", NULL } ;
 
static const char *brw1[] = { "librewolf", NULL };

/* static const char *brw1[] = { "com.github.Eloston.UngoogledChromium", "--password-store='lxpolkit'", "--ignore-gpu-blocklist", "--enable-gpu-rasterization", "--enable-zero-copy", "--disable-features=UseChromeOSDirectVideoDecoder", "--disk-cache-dir=/dev/null", "--use-angle=vulkan", "--max_old_space_size=8126", NULL }; */

/* static const char *incognito = { "com.github.Eloston.UngoogledChromium", "--incognito", "--password-store='lxpolkit'", NULL }; */

static const char *github[] = { "io.github.shiftey.Desktop", NULL };
static const char *vpn[] = { "riseup-vpn.launcher", NULL }; 

/* photo */

static const char *pe[] = { "gimp", "-n", "-a",  NULL };
static const char *pv[] = { "nomacs", "-p", "-d" "$HOME/Pictures", NULL }; 
static const char *c[] = { "org.kde.kcolorchooser", NULL };

/* video */

static const char *ve[] = { "kdenlive", NULL };
/* static const char *vv[] = { "vlc", NULL }; */

/* audio */

static const char *daw1[] = { "bitwig-studio", NULL };

static const char *m1[] = { "com.spotify.Client", NULL };
static const char *m2[] = { "deadbeef", NULL };
static const char *m3[] = { "alacritty", "-e", "cmus", NULL };

static const char *radio1[] = { "goodvibes", NULL };
static const char *radio2[] = { "de.haeckerfelix.Shortwave", NULL };

/* gaming */

static const char *steam[] = { "steam", NULL };
static const char *game1[] = { "cool-retro-term", "-e", "cataclysm", NULL };
static const char *game2[] = { "openttd", NULL };

/* cleaners */

static const char *cleaner[] = { "alacritty", "-e", "sudo", "bleachbit", NULL };
static const char *cleaner2[] = { "alacritty", "-e" "sudo", "stacer", NULL };

/* visualizer */

static const char *visualizer[] = { "alacritty", "-e", "cmatrix", "-r", NULL };

/* commands */

static Key keys[] = {

	/* modifier             key     	function     	argument */

	/* access configuration */

	{ MODKEY,		XK_slash,	spawn,		{ .v = dwmcon1 } },
	{ MODKEY|ShiftMask,	XK_slash,	spawn,          { .v = dwmcon2 } },

	/* utility */

					
	{ Mod1Mask,		XK_p,		spawn,		{ .v = dmenucmd } },
	{ Mod1Mask,		XK_grave,	spawn,  	{ .v = rofi } },
	{ MODKEY,		XK_grave,	spawn,		{ .v = dmenucmd } }, 		
	{ MODKEY,		XK_p,		spawn,		{ .v = rofi } },

	
	{ Mod1Mask,		XK_F1,		spawn,		{ .v = dmenucmd } },
	{ Mod1Mask,		XK_F2,		spawn,		{ .v = rofi } },

	{ MODKEY|ShiftMask,	XK_Return, 	    spawn,      { .v = termcmd } },
	{ Mod1Mask|ShiftMask,	XK_Return, 	spawn, 	        { .v = termcmd2 } },
	{ ControlMask|Mod1Mask, XK_t,		spawn,	        { .v = termcmd } },
	{ Mod1Mask,		XK_Escape,	        spawn,  { .v = termcmd } },	
	
	{ MODKEY|ShiftMask,	XK_t,		spawn,		{ .v = termcmd } },

	{ ShiftMask,		XK_Print,	spawn,		{ .v = ssf } },
	
	{ 0,			XK_Print,	spawn,		{ .v = ss } },	

	{ MODKEY,		XK_Print,	spawn,		{ .v = sr } },
	
	{ ControlMask,		XK_Escape,	spawn,		{ .v = pwmgr } },	
	{ ShiftMask, 		XK_Escape,	spawn,		{ .v = sysmon } },

	{ MODKEY|ShiftMask,	XK_f,		spawn,		{ .v = fm1 } },	
	{ MODKEY|ControlMask, 	XK_f, 		spawn,  	{ .v = fm2 } },
	
	{ MODKEY|ShiftMask,	XK_e,		spawn,		{ .v = editor } },	
	{ MODKEY|ControlMask, 	XK_e, 		spawn,    	{ .v = viewer } },

	{ MODKEY|ControlMask,   XK_period,	spawn,		{ .v = emoji } },
	
	
	{ MODKEY|ControlMask, 	XK_v, 		spawn,		{ .v = visualizer } },
	{ MODKEY|ControlMask,   XK_t,           spawn,          { .v = transset } },

	/* system control */
	
	{ 0,	XF86XK_MonBrightnessUp,		spawn,		{ .v = screenup } },
	{ 0,	XF86XK_MonBrightnessDown, 	spawn,		{ .v = screendown } },
	
	{ MODKEY,         XK_F4,		spawn,		{ .v = screenup } },	
	{ MODKEY,         XK_F3,		spawn,		{ .v = screendown } },
	
	{ 0,	XF86XK_KbdBrightnessUp,		spawn,		{ .v = kbdup } },
	{ 0,	XF86XK_KbdBrightnessDown,	spawn,		{ .v = kbddown } },
	
	{ MODKEY,	XF86XK_AudioMute,	spawn,		{ .v = mutemic } },
	{ MODKEY|ShiftMask,	XF86XK_AudioMute,	spawn,	{ .v = mutemicb } },
	
	{ MODKEY,	XK_Escape,		spawn,		{ .v = mutemic } },	
	{ MODKEY,	XK_backslash,		spawn,		{ .v = mutemic } }, 
	{ 0,	XK_F12,				spawn,		{ .v = mutemic } },
	{ MODKEY|ShiftMask,	XK_Escape,		spawn,	{ .v = mutemicb } },
	{ ControlMask|MODKEY, XK_Escape,    spawn,              { .v = killmicboost } },

 	{ MODKEY,	XF86XK_AudioRaiseVolume, spawn,		{ .v = upmica } },
	{ MODKEY,	XF86XK_AudioLowerVolume, spawn,		{ .v = downmica } },

	{ ControlMask,	XF86XK_AudioRaiseVolume, spawn,	        { .v = upmicb } },
	{ ControlMask,	XF86XK_AudioLowerVolume, spawn,	        { .v = downmicb } },
		
	{ 0,	XF86XK_AudioRaiseVolume,	spawn,		{ .v = emiup } },

	{ 0,	XF86XK_AudioLowerVolume,	spawn,		{ .v = emidown } },

	{ Mod1Mask, XF86XK_AudioRaiseVolume, spawn,             { .v = plyvolup } },

	{ Mod1Mask, XF86XK_AudioLowerVolume, spawn,             { .v = plyvoldown } },

	{ MODKEY,	XK_F2,	spawn,		                { .v = emiup } },

	{ MODKEY,	XK_F1,	spawn,		                { .v = emidown } },

	{ MODKEY|ShiftMask, XK_F1, spawn,	                { .v = downmica } },

	{ MODKEY|ShiftMask, XK_F2, spawn,	                { .v = upmica } },

	{ 0,	XF86XK_AudioMute,		spawn,		{ .v = mutevol } }, 
	
	{ 0,	XF86XK_AudioStop,		spawn,		{ .v = plystop } },

	{ 0,	XF86XK_AudioPlay,		spawn,		{ .v = plyplay } },
	
	{ 0,	XF86XK_AudioNext,		spawn,		{ .v = plynext } },

	{ 0, 	XF86XK_AudioPrev,		spawn,		{ .v = plyprev } },

	{ MODKEY,	XF86XK_AudioNext,	spawn,	{ .v = plyfore } },

	{ MODKEY,	XF86XK_AudioPrev,	spawn,	{ .v = plyback } },

	{ ControlMask,	XF86XK_AudioNext,	spawn,	{ .v = plyfore2 } },

	{ ControlMask,	XF86XK_AudioPrev,	spawn,  { .v = plyback2 } },
	
	{ Mod1Mask,      XF86XK_AudioPlay,      spawn,         { .v = plyloop } },

	{ Mod1Mask|ShiftMask,      XF86XK_AudioPlay,  spawn,   { .v = plyloop2 } },

	{ ControlMask|Mod1Mask,    XF86XK_AudioPlay,       spawn,      { .v = plyloop3 } },
	
	/* quit */

	{ MODKEY,		  XK_End,	quit,		  {0} },
	{ Mod1Mask|ShiftMask,	  XK_Escape,    quit,	          {0} },
	{ ControlMask|Mod1Mask,	  XK_Delete,    quit,	          {0} },

	/* cleaners */	

	{ MODKEY,		  XK_Delete,	spawn,		{ .v = cleaner } }, 
	{ MODKEY|Mod1Mask,                 XK_Delete,    spawn,          { .v = cleaner2 } },

	/* web */

	{ MODKEY|ShiftMask,     XK_i,	        spawn,		{ .v = msg1 } },
	{ MODKEY|ControlMask,	XK_i,		spawn,		{ .v = vpn } },

	{ MODKEY,		XK_w,	        spawn,		{ .v = brw1 } },
	{ MODKEY|ShiftMask,	XK_w,	        spawn,		{ .v = msg1 } },

	{ MODKEY|ControlMask,	XK_w,		spawn,		{ .v = github } },

	{ ControlMask|Mod1Mask,	XK_m,		spawn,		{ .v = mail } },	
	{ MODKEY|ControlMask,   XK_n,           spawn,          { .v = nicotine } },
	
	/* audio */

	{ MODKEY|ShiftMask,	   XK_m,		spawn,		{ .v = m1 } },
	{ MODKEY|ControlMask,       XK_m,		spawn,		{ .v = m2 } },

	{ MODKEY|Mod1Mask,         XK_m,        spawn,                  { .v = m3 } },
	
	{ MODKEY,		   XK_r,		spawn,		{ .v = radio1 } },
	{ MODKEY|ShiftMask,	   XK_r,		spawn,		{ .v = radio2 } },
	
	{ Mod1Mask,		   XK_d,		spawn,		{ .v = daw1 } },
	

	{ MODKEY,		XK_s,		spawn,		{ .v = sctrl1 } },
	{ MODKEY|ShiftMask,	XK_s,		spawn,		{ .v = sctrl2 } },
	{ MODKEY|ControlMask,	XK_s,		spawn,		{ .v = sctrl3 } },	
	
	/* photo */

	{ MODKEY,		XK_p,		spawn,		{ .v = pv } },
	{ Mod1Mask,		XK_c,		spawn,		{ .v = c } },
	{ MODKEY|ShiftMask,	XK_p,		spawn,		{ .v = pe } },
	
	{ MODKEY|ShiftMask,	XK_n,		spawn,		{ .v = wp } },
	
	/* video */

	{ MODKEY,		    XK_v,		spawn,		{ .v = vv } },	
	{ MODKEY|ShiftMask,	XK_v,		spawn,		{ .v = ve } },

	/* gaming */

	{ MODKEY,		XK_g,		spawn,		{ .v = game1 } },	
	{ MODKEY|ShiftMask,	XK_g, 		spawn,		{ .v = game2 } },
	{ ControlMask|MODKEY,	XK_g,		spawn,		{ .v = steam } },
	
	/* layouts, focus, etc. */
	
	{ Mod1Mask,		XK_f,		togglecanfocusfloating,		{0} },

	{ MODKEY,               XK_b,      	togglebar,      { 0 } },
	
	{ MODKEY,               XK_j,      	focusstack,     { .i = +1 } },
	{ MODKEY,               XK_k,      	focusstack,     { .i = -2 } },
	{ MODKEY,               XK_e,      	focusstack,     { .i = +1 } },
	{ MODKEY,               XK_q,      	focusstack,     { .i = -2 } },
	{ MODKEY,               XK_Up,      	focusstack,     { .i = +1 } },
	{ MODKEY,               XK_Down,      	focusstack,     { .i = -2 } },
	
	{ Mod1Mask|ShiftMask,               XK_i,      	incnmaster,     { .i = +1 } },
	{ Mod1Mask|ShiftMask,               XK_d,      	incnmaster,     { .i = -1 } },
	
	{ MODKEY,               XK_h,      	setmfact,       { .f = -0.02 } },
	{ MODKEY,               XK_l,      	setmfact,       { .f = +0.02 } },
	{ MODKEY,               XK_a,      	setmfact,       { .f = -0.02 } },
	{ MODKEY,               XK_d,      	setmfact,       { .f = +0.02 } },
	
	{ MODKEY,               XK_Return, 	zoom,           { 0 } },
	{ MODKEY,               XK_Tab, 	zoom,           { 0 } },
	{ Mod1Mask,             XK_Tab,    	view,           { 0 } },	
	{ MODKEY|ShiftMask,     XK_q,      	killclient,     { 0 } },
	{ Mod1Mask,             XK_q,           killclient,     { 0 } },
	{ Mod1Mask,     	XK_F4,      	killclient,     { 0 } },
	
	{ MODKEY,               XK_t,      	setlayout,      { .v = &layouts[0] } },
	{ MODKEY,               XK_f,      	setlayout,      { .v = &layouts[1] } },
	{ MODKEY,               XK_m,      	setlayout,      { .v = &layouts[2] } },
	{ MODKEY,               XK_y,      	setlayout,      { .v = &layouts[3] } },
	{ ControlMask|MODKEY,   XK_y,       setlayout,      { .v = &layouts[4] } },
	{ MODKEY|ShiftMask,     XK_y,       setlayout,      { .v = &layouts[5] } },
	
	{ MODKEY|ShiftMask,     XK_space,  	togglefloating, { 0 } },
	{ MODKEY,               XK_space,  	setlayout,      { 0 } },
	
	{ MODKEY,               XK_0,      	view,           { .ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,      	tag,           	{ .ui = ~0 } },
	
	{ MODKEY,               XK_comma,  	focusmon,      	{ .i = -1 } },
	{ MODKEY,               XK_period, 	focusmon,      	{ .i = +1 } },
	{ MODKEY,               XK_z,  		focusmon,      	{ .i = -1 } },
	{ MODKEY,               XK_c, 		focusmon,      	{ .i = +1 } },
	{ MODKEY,               XK_Left,  	focusmon,      	{ .i = -1 } },
	{ MODKEY,               XK_Right, 	focusmon,      	{ .i = +1 } },
	
	{ MODKEY|ShiftMask,     XK_comma,  	tagmon,        	{ .i = -1 } },
	{ MODKEY|ShiftMask,     XK_period, 	tagmon,         { .i = +1 } },
	{ MODKEY|ShiftMask,     XK_z,  		tagmon,        	{ .i = -1 } },
	{ MODKEY|ShiftMask,     XK_c, 		tagmon,         { .i = +1 } },
	{ MODKEY|ShiftMask,     XK_Left,  	tagmon,        	{ .i = -1 } },
	{ MODKEY|ShiftMask,     XK_Right, 	tagmon,         { .i = +1 } },
	
	{ MODKEY,               XK_bracketleft,  setgaps,       {.i = -2 } },
	{ MODKEY,               XK_bracketright, setgaps,       {.i = +2 } },
	{ MODKEY|ShiftMask,   	XK_bracketleft,	 setgaps,       {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,     XK_bracketright, setgaps,       {.i = GAP_TOGGLE} },
	
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
