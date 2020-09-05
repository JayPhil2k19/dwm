void
movethrow(const Arg *arg)
{
	Client *c;
	int nh, nw, nx, ny;
	c = selmon->sel;
	if (selmon->lt[selmon->sellt]->arrange && !c->isfloating)
		togglefloating(NULL);
	nw = c->w;
	nh = c->h;
    switch(arg->ui) {
        case DIR_N:
            nx = c->x;
            ny = selmon->wy;
            break;
        case DIR_E:
            nx = selmon->wx + selmon->ww - c->w - c->bw*2;
            ny = c->y;
            break;
        case DIR_S:
            nx = c->x;
            ny = selmon->wy + selmon->wh - c->h - c->bw*2;
            break;
        case DIR_W:
            nx = selmon->wx;
            ny = c->y;
            break;
        case DIR_C:
            nx = selmon->wx + ((selmon->ww - c->w - c->bw*2) / 2);
            ny = selmon->wy + ((selmon->wh - c->h - c->bw*2) / 2);
            break;
        default:
            return;
    }
	resize(c, nx, ny, nw, nh, True);
   XWarpPointer(dpy, None, c->win, 0, 0, 0, 0, nw/2, nh/2);
}
