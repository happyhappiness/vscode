static void refresh(int verbose, const struct pathspec *pathspec)
{
	char *seen;
	int i;

	seen = xcalloc(pathspec->nr, 1);
	refresh_index(&the_index, verbose ? REFRESH_IN_PORCELAIN : REFRESH_QUIET,
		      pathspec, seen, _("Unstaged changes after refreshing the index:"));
	for (i = 0; i < pathspec->nr; i++) {
		if (!seen[i])
			die(_("pathspec '%s' did not match any files"),
			    pathspec->items[i].match);
	}
        free(seen);
}