typedef struct Workspace Workspace;
struct Workspace {
	unsigned int tagset;
	Layout *lt;
	float mfact;
};

static Workspace workspaces[] = {
	/* tagset						layout			fact */
	{ (1 << 0),						&layouts[0],	0.55},
	{ (1 << 0) | (1<< 8),			&layouts[0],	0.75},
	{ (1 << 0) | (1<< 1) | (1<< 8),	&layouts[1],	0},
	{ (1<< 8),						&layouts[2],	0},
};

static unsigned int ws = 0;

static void
setws(int nws) {
	workspaces[ws].tagset = tagset[seltags];
	workspaces[ws].lt = lt[sellt];
	workspaces[ws].mfact = (workspaces[ws].lt == &layouts[0]) ? mfact : 0;
	if(nws < LENGTH(workspaces))
		ws = nws;
	if(workspaces[ws].tagset) {
		tagset[seltags] = workspaces[ws].tagset;
		lt[sellt] = workspaces[ws].lt;
		if(workspaces[ws].mfact != 0)
			mfact = workspaces[ws].mfact;
		arrange();
	}
}

static void
prevws(const Arg *arg) {
	setws((ws == 0) ? LENGTH(workspaces) - 1 : ws - 1);
}

static void
nextws(const Arg *arg) {
	setws((ws == LENGTH(workspaces) - 1) ? 0 : ws + 1);
}
