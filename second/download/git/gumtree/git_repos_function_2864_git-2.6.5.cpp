int ref_is_hidden(const char *refname)
{
	int i;

	if (!hide_refs)
		return 0;
	for (i = hide_refs->nr - 1; i >= 0; i--) {
		const char *match = hide_refs->items[i].string;
		int neg = 0;
		int len;

		if (*match == '!') {
			neg = 1;
			match++;
		}

		if (!starts_with(refname, match))
			continue;
		len = strlen(match);
		if (!refname[len] || refname[len] == '/')
			return !neg;
	}
	return 0;
}