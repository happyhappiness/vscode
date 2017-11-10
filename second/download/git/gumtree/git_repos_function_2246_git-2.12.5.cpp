static size_t common_prefix_len(const struct pathspec *pathspec)
{
	int n;
	size_t max = 0;

	/*
	 * ":(icase)path" is treated as a pathspec full of
	 * wildcard. In other words, only prefix is considered common
	 * prefix. If the pathspec is abc/foo abc/bar, running in
	 * subdir xyz, the common prefix is still xyz, not xuz/abc as
	 * in non-:(icase).
	 */
	GUARD_PATHSPEC(pathspec,
		       PATHSPEC_FROMTOP |
		       PATHSPEC_MAXDEPTH |
		       PATHSPEC_LITERAL |
		       PATHSPEC_GLOB |
		       PATHSPEC_ICASE |
		       PATHSPEC_EXCLUDE);

	for (n = 0; n < pathspec->nr; n++) {
		size_t i = 0, len = 0, item_len;
		if (pathspec->items[n].magic & PATHSPEC_EXCLUDE)
			continue;
		if (pathspec->items[n].magic & PATHSPEC_ICASE)
			item_len = pathspec->items[n].prefix;
		else
			item_len = pathspec->items[n].nowildcard_len;
		while (i < item_len && (n == 0 || i < max)) {
			char c = pathspec->items[n].match[i];
			if (c != pathspec->items[0].match[i])
				break;
			if (c == '/')
				len = i + 1;
			i++;
		}
		if (n == 0 || len < max) {
			max = len;
			if (!max)
				break;
		}
	}
	return max;
}