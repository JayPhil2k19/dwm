/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack-bold:size=18:style=bold" };
static const char dmenufont[]       = "Hack-bold:size=16:style=bold";
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#000000";
static const char col_cyan[]        = "#0754EE";
static const char col_red[]        = "#FEDA00";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeInv]  = { col_gray1, col_gray3, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_red  },
//	[SchemeTitle]  = { col_gray4, col_cyan,  col_cyan  },

	[SchemeStatus]  = { col_gray3, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray4, col_cyan,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_gray4, col_cyan,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};


static char* const autostart[][2] = { /* please replace 2 with maximum number of arguments from autostart array */
    { "st", NULL },
//    { "dwmblocks", NULL },
};

/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           0,           -1 },
};

/* layout(s) */

#include "horizgrid.c"
#include "layouts.c"
#include "fibonacci.c"
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "👻",      NULL },    /* no layout function means floating behavior */
	{ "🌑",      monocle },
	{ NULL,       NULL },
	{ "",       horizgrid },
	{ "",       grid },
	{ "",      centeredmaster },
	{ "",      centeredfloatingmaster },
	{ "",     spiral },
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
static const char *dmenucmd[] = { "dmenu_run","-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, topbar ? NULL : "-b", NULL };
static const char *termcmd[]  = { "st", NULL };
/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
static char *statuscmds[] = { "notify-send Mouse$BUTTON" };
static char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g","-f Hack-bold:size=24" "120x32", NULL };
#include "movestack.c"
#include "selfrestart.c"
#include <X11/XF86keysym.h>
#include "mpdcontrol.c"
#include "focusurgent.c"
#include "movethrow.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,         SHCMD("~/scr/dmenufm") },
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
    	{ MODKEY|ShiftMask,             XK_Up,     movethrow,      {.ui = DIR_N  }},
    	{ MODKEY|ShiftMask,             XK_Down,   movethrow,      {.ui = DIR_S  }},
    	{ MODKEY|ShiftMask,             XK_Left,   movethrow,      {.ui = DIR_W  }},
    	{ MODKEY|ShiftMask,             XK_Right,  movethrow,      {.ui = DIR_E  }},
    	{ MODKEY|ShiftMask,             XK_m,      movethrow,      {.ui = DIR_C  }},
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             		XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_x,      killunsel,      {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_h,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = +5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY|ShiftMask,             XK_u,      focusurgent,    {0} },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          SHCMD("~/scr/timer.sh") },
	{ Mod1Mask|ControlMask,		XK_Return,    spawn,          SHCMD("~/run-xmenu.sh && aplay ~/Sounds/frying_pan_hit.wav") },
	{ 0, XF86XK_AudioPrev,          spawn,          SHCMD("mpc prev") },
        { 0, XF86XK_AudioNext,          spawn,          SHCMD("mpc next") },
        { 0, XF86XK_AudioPlay,          spawn,          SHCMD("mpc toggle ; ~/conky-start.sh") },
        { 0, XF86XK_AudioStop,          spawn,          SHCMD("mpc stop ; ~/conky-stop.sh") },
        { 0, XF86XK_AudioMute,          spawn,          SHCMD("amixer -D pulse sset Master toggle") },
        { 0, XF86XK_AudioRaiseVolume,   spawn,          SHCMD("amixer -D pulse sset Master 5%+") },
        { 0, XF86XK_AudioLowerVolume,   spawn,          SHCMD("amixer -D pulse sset Master 5%-") },
        { 0, XF86XK_Tools,              spawn,          SHCMD("st -e ncmpcpp") },
        { 0, XF86XK_Mail,               spawn,          SHCMD("st -e neomutt") },
        { 0, XF86XK_Search,             spawn,          SHCMD("st -e ranger") },
        { 0, XF86XK_HomePage,           spawn,          SHCMD("brave") },
	{ 0, XK_Print,                  spawn,          SHCMD("scrot -e 'mv $f ~/Pictures/Screenshots/' && aplay ~/Sounds/camera1.wav ") },
 	{ Mod1Mask,                     XK_minus,  spawn,          SHCMD("amixer sset Master 5%- && aplay ~/Sounds/beep_ping.wav ") },
        { Mod1Mask|ShiftMask,             XK_minus,  spawn,          SHCMD("amixer sset Master 25%- && aplay ~/Sounds/beep_ping.wav  ") },
        { Mod1Mask,                       XK_equal,  spawn,          SHCMD("amixer sset Master 5%+ && aplay ~/Sounds/beep_ping.wav  ") },
        { Mod1Mask|ShiftMask,             XK_equal,  spawn,          SHCMD("amixer sset Master 25%+  && aplay ~/Sounds/beep_ping.wav ") },
        { Mod1Mask,           		XK_BackSpace, spawn,       SHCMD("amixer sset Master toggle") },
        { Mod1Mask,           		XK_p,      spawn,          SHCMD("mpc toggle ; ~/conky-start.sh") },
        { Mod1Mask,           		XK_s,      spawn,          SHCMD("mpc stop ; ~/conky-stop.sh") },
        { Mod1Mask,           		XK_bracketleft, spawn,     SHCMD("mpc prev") },
        { Mod1Mask,           		XK_bracketright, spawn,    SHCMD("mpc next") },
        { Mod1Mask,           		XK_r,      spawn,          SHCMD("mpc repeat") },
        { Mod1Mask,           		XK_z,      spawn,          SHCMD("mpc random") },
	{ MODKEY,                       XK_F7,      spawn,          SHCMD("~/scr/dmenu_mpd_ctrl.sh") },
        { MODKEY,                       XK_F12,     spawn,          SHCMD("~/scr/dmenu_mpd_search.sh") },
        { Mod1Mask,                     XK_F7,      spawn,           SHCMD("feh -rz --bg-scale ~/Pictures/Wallpapers/*") },
        { Mod1Mask|ShiftMask,           XK_c,       spawn,          SHCMD("conky -c ~/.conky_music") },
	{ ControlMask,        		XK_minus, 		setborderpx,    {.i = -1 } },
	{ ControlMask,        		XK_minus, 		setborderpx,    {.i = +1 } },
	{ ControlMask|ShiftMask,        XK_minus, 		setborderpx,    {.i = -5 } },
	{ ControlMask|ShiftMask,        XK_equal, 		setborderpx,    {.i = +5 } },
	{ ControlMask|ShiftMask,        XK_0, 	setborderpx,    {.i = 0 } },
	{ ControlMask|Mod1Mask,		XK_End,  spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Shutdown?\")\" = Yes ] && aplay ~/Sounds/computer_magic.wav && systemctl poweroff") },
	{ ControlMask|Mod1Mask,		XK_Home,	    spawn,	SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Logout?\")\" = Yes ] && aplay ~/Sounds/laser_x.wav && killall Xorg") },
	{ ControlMask|Mod1Mask,		XK_Delete,	spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Reboot?\")\" = Yes ] && aplay ~/Sounds/computer_reboot.wav && sudo -A reboot") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    	{ MODKEY|ShiftMask,             XK_r,      self_restart,   {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,                       XK_F1,     mpdchange,      {.i = -1} },
	{ MODKEY,                       XK_F2,     mpdchange,      {.i = +1} },
	{ MODKEY,           		XK_F4,      spawn,          SHCMD("mpc repeat") },
        { MODKEY,           		XK_F3,      spawn,          SHCMD("mpc random") },
	{ MODKEY,                       XK_Escape, mpdcontrol,     {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = statuscmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        spawn,      SHCMD("~/run-xmenu.sh") },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
//	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button2,        toggletag,      {0} },
	{ ClkTagBar,            MODKEY,         Button3,        spawn,      SHCMD("~/run-xmenu.sh") },
};
