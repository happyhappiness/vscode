static const char *lstrip_ref_components(const char *refname, int len)
{
	long remaining = len;
	const char *start = refname;

	if (len < 0) {
		int i;
		const char *p = refname;

		/* Find total no of '/' separated path-components */
		for (i = 0; p[i]; p[i] == '/' ? i++ : *p++)
			;
		/*
		 * The number of components we need to strip is now
		 * the total minus the components to be left (Plus one
		 * because we count the number of '/', but the number
		 * of components is one more than the no of '/').
		 */
		remaining = i + len + 1;
	}

	while (remaining > 0) {
		switch (*start++) {
		case '\0':
			return "";
		case '/':
			remaining--;
			break;
		}
	}

	return start;
}