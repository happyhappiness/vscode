static int match_pattern(const char **patterns, const char *ref)
{
	/* no pattern means match everything */
	if (!*patterns)
		return 1;
	for (; *patterns; patterns++)
		if (!wildmatch(*patterns, ref, 0, NULL))
			return 1;
	return 0;
}