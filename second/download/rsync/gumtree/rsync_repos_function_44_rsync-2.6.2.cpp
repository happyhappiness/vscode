void send_exclude_list(int f)
{
	struct exclude_struct *ent;

	/* This is a complete hack - blame Rusty.
	 *
	 * FIXME: This pattern shows up in the output of
	 * report_exclude_result(), which is not ideal. */
	if (list_only && !recurse)
		add_exclude(&exclude_list, "/*/*", 0);

	for (ent = exclude_list.head; ent; ent = ent->next) {
		unsigned int l;
		char p[MAXPATHLEN+1];

		l = strlcpy(p, ent->pattern, sizeof p);
		if (l == 0 || l >= MAXPATHLEN)
			continue;
		if (ent->directory) {
			p[l++] = '/';
			p[l] = '\0';
		}

		if (ent->include) {
			write_int(f, l + 2);
			write_buf(f, "+ ", 2);
		} else if ((*p == '-' || *p == '+') && p[1] == ' ') {
			write_int(f, l + 2);
			write_buf(f, "- ", 2);
		} else
			write_int(f, l);
		write_buf(f, p, l);
	}

	write_int(f, 0);
}