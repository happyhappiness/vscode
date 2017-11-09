int ref_is_hidden(const char *refname, const char *refname_full)
{
	int i;

	if (!hide_refs)
		return 0;
	for (i = hide_refs->nr - 1; i >= 0; i--) {
		const char *match = hide_refs->items[i].string;
		const char *subject;
		int neg = 0;
		const char *p;

		if (*match == '!') {
			neg = 1;
			match++;
		}

		if (*match == '^') {
			subject = refname_full;
			match++;
		} else {
			subject = refname;
		}

		/* refname can be NULL when namespaces are used. */
		if (subject &&
		    skip_prefix(subject, match, &p) &&
		    (!*p || *p == '/'))
			return !neg;
	}
	return 0;
}