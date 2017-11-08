void add_exclude(struct exclude_list_struct *listp, const char *pattern,
		 int xflags)
{
	int pat_len, incl;
	const char *cp;

	if (!pattern)
		return;

	cp = pattern;
	pat_len = 0;
	while (1) {
		cp = get_exclude_tok(cp + pat_len, &pat_len, &incl, xflags);
		if (!pat_len)
			break;
		/* If we got the special "!" token, clear the list. */
		if (incl < 0)
			free_exclude_list(listp);
		else {
			make_exclude(listp, cp, pat_len, incl);

			if (verbose > 2) {
				rprintf(FINFO, "[%s] add_exclude(%.*s, %s%s)\n",
					who_am_i(), pat_len, cp,
					listp->debug_type,
					incl ? "include" : "exclude");
			}
		}
	}
}