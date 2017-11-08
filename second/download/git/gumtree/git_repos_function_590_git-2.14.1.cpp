static int match_pattern(const struct ref_filter *filter, const char *refname)
{
	const char **patterns = filter->name_patterns;
	unsigned flags = 0;

	if (filter->ignore_case)
		flags |= WM_CASEFOLD;

	/*
	 * When no '--format' option is given we need to skip the prefix
	 * for matching refs of tags and branches.
	 */
	(void)(skip_prefix(refname, "refs/tags/", &refname) ||
	       skip_prefix(refname, "refs/heads/", &refname) ||
	       skip_prefix(refname, "refs/remotes/", &refname) ||
	       skip_prefix(refname, "refs/", &refname));

	for (; *patterns; patterns++) {
		if (!wildmatch(*patterns, refname, flags))
			return 1;
	}
	return 0;
}