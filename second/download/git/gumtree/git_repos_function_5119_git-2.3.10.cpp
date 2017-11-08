static char *collapse_slashes(const char *refname)
{
	char *ret = xmalloc(strlen(refname) + 1);
	char ch;
	char prev = '/';
	char *cp = ret;

	while ((ch = *refname++) != '\0') {
		if (prev == '/' && ch == prev)
			continue;

		*cp++ = ch;
		prev = ch;
	}
	*cp = '\0';
	return ret;
}