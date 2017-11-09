static int looks_like_pathspec(const char *arg)
{
	/* anything with a wildcard character */
	if (!no_wildcard(arg))
		return 1;

	/* long-form pathspec magic */
	if (starts_with(arg, ":("))
		return 1;

	return 0;
}