static int match_patterns(const char **pattern, const char *refname)
{
	if (!*pattern)
		return 1; /* no pattern always matches */
	while (*pattern) {
		if (!wildmatch(*pattern, refname, 0, NULL))
			return 1;
		pattern++;
	}
	return 0;
}