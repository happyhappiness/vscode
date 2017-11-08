static int simplify_away(const char *path, int pathlen,
			 const struct pathspec *pathspec)
{
	int i;

	if (!pathspec || !pathspec->nr)
		return 0;

	GUARD_PATHSPEC(pathspec,
		       PATHSPEC_FROMTOP |
		       PATHSPEC_MAXDEPTH |
		       PATHSPEC_LITERAL |
		       PATHSPEC_GLOB |
		       PATHSPEC_ICASE |
		       PATHSPEC_EXCLUDE |
		       PATHSPEC_ATTR);

	for (i = 0; i < pathspec->nr; i++) {
		const struct pathspec_item *item = &pathspec->items[i];
		int len = item->nowildcard_len;

		if (len > pathlen)
			len = pathlen;
		if (!ps_strncmp(item, item->match, path, len))
			return 0;
	}

	return 1;
}