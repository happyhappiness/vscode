static int match_name_as_path(const char **pattern, const char *refname)
{
	int namelen = strlen(refname);
	for (; *pattern; pattern++) {
		const char *p = *pattern;
		int plen = strlen(p);

		if ((plen <= namelen) &&
		    !strncmp(refname, p, plen) &&
		    (refname[plen] == '\0' ||
		     refname[plen] == '/' ||
		     p[plen-1] == '/'))
			return 1;
		if (!wildmatch(p, refname, WM_PATHNAME, NULL))
			return 1;
	}
	return 0;
}