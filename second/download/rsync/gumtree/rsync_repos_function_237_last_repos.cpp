void set_compression(const char *fname)
{
	const struct suffix_tree *node;
	const char *s;
	char ltr;

	if (!do_compression)
		return;

	if (!match_list)
		init_set_compression();

	compression_level = per_file_default_level;

	if (!*match_list && !suftree)
		return;

	if ((s = strrchr(fname, '/')) != NULL)
		fname = s + 1;

	for (s = match_list; *s; s += strlen(s) + 1) {
		if (iwildmatch(s, fname)) {
			compression_level = 0;
			return;
		}
	}

	if (!(node = suftree) || !(s = strrchr(fname, '.'))
	 || s == fname || !(ltr = *++s))
		return;

	while (1) {
		if (isUpper(&ltr))
			ltr = toLower(&ltr);
		while (node->letter != ltr) {
			if (node->letter > ltr)
				return;
			if (!(node = node->sibling))
				return;
		}
		if ((ltr = *++s) == '\0') {
			if (node->word_end)
				compression_level = 0;
			return;
		}
		if (!(node = node->child))
			return;
	}
}