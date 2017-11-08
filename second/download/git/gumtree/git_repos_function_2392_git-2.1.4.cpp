static int check_refname_component(const char *refname, int flags)
{
	const char *cp;
	char last = '\0';

	for (cp = refname; ; cp++) {
		int ch = *cp & 255;
		unsigned char disp = refname_disposition[ch];
		switch (disp) {
		case 1:
			goto out;
		case 2:
			if (last == '.')
				return -1; /* Refname contains "..". */
			break;
		case 3:
			if (last == '@')
				return -1; /* Refname contains "@{". */
			break;
		case 4:
			return -1;
		}
		last = ch;
	}
out:
	if (cp == refname)
		return 0; /* Component has zero length. */
	if (refname[0] == '.') {
		if (!(flags & REFNAME_DOT_COMPONENT))
			return -1; /* Component starts with '.'. */
		/*
		 * Even if leading dots are allowed, don't allow "."
		 * as a component (".." is prevented by a rule above).
		 */
		if (refname[1] == '\0')
			return -1; /* Component equals ".". */
	}
	if (cp - refname >= 5 && !memcmp(cp - 5, ".lock", 5))
		return -1; /* Refname ends with ".lock". */
	return cp - refname;
}