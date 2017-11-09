static int exclude_matches_pathspec(const char *path, int pathlen,
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
		       PATHSPEC_EXCLUDE);

	for (i = 0; i < pathspec->nr; i++) {
		const struct pathspec_item *item = &pathspec->items[i];
		int len = item->nowildcard_len;

		if (len == pathlen &&
		    !ps_strncmp(item, item->match, path, pathlen))
			return 1;
		if (len > pathlen &&
		    item->match[pathlen] == '/' &&
		    !ps_strncmp(item, item->match, path, pathlen))
			return 1;
	}
	return 0;
}