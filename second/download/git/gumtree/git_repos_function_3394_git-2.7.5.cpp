static void prepare_order(const char *orderfile)
{
	int cnt, pass;
	struct strbuf sb = STRBUF_INIT;
	void *map;
	char *cp, *endp;
	ssize_t sz;

	if (order)
		return;

	sz = strbuf_read_file(&sb, orderfile, 0);
	if (sz < 0)
		die_errno(_("failed to read orderfile '%s'"), orderfile);
	map = strbuf_detach(&sb, NULL);
	endp = (char *) map + sz;

	for (pass = 0; pass < 2; pass++) {
		cnt = 0;
		cp = map;
		while (cp < endp) {
			char *ep;
			for (ep = cp; ep < endp && *ep != '\n'; ep++)
				;
			/* cp to ep has one line */
			if (*cp == '\n' || *cp == '#')
				; /* comment */
			else if (pass == 0)
				cnt++;
			else {
				if (*ep == '\n') {
					*ep = 0;
					order[cnt] = cp;
				} else {
					order[cnt] = xmemdupz(cp, ep - cp);
				}
				cnt++;
			}
			if (ep < endp)
				ep++;
			cp = ep;
		}
		if (pass == 0) {
			order_cnt = cnt;
			ALLOC_ARRAY(order, cnt);
		}
	}
}