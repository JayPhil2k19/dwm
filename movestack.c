void
movestack(const Arg *arg) {
	Client *c = NULL, *p = NULL, *pc = NULL, *i;

	if(arg->i > 0) {
		/* find the client after sel */
		for(c = sel->next; c && (!ISVISIBLE(c) || c->isfloating); c = c->next);
		if(!c)
			for(c = clients; c && (!ISVISIBLE(c) || c->isfloating); c = c->next);

	}
	else {
		/* find the client before sel */
		for(i = clients; i != sel; i = i->next)
			if(ISVISIBLE(i) && !i->isfloating)
				c = i;
		if(!c)
			for(; i; i = i->next)
				if(ISVISIBLE(i) && !i->isfloating)
					c = i;
	}
	/* find the client before sel and c */
	for(i = clients; i && (!p || !pc); i = i->next) {
		if(i->next == sel)
			p = i;
		if(i->next == c)
			pc = i;
	}

	/* swap c and sel clients in the clients list */
	if(c && c != sel) {
		Client *temp = sel->next==c?sel:sel->next;
		sel->next = c->next==sel?c:c->next;
		c->next = temp;

		if(p && p != c)
			p->next = c;
		if(pc && pc != sel)
			pc->next = sel;

		if(sel == clients)
			clients = c;
		else if(c == clients)
			clients = sel;

		arrange();
	}
}
