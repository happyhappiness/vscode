	hold_locked_index(&lock_file, LOCK_DIE_ON_ERROR);

	if (read_cache() < 0)
		die(_("index file corrupt"));

	parse_pathspec(&pathspec, 0,
		       PATHSPEC_PREFER_CWD |
		       PATHSPEC_STRIP_SUBMODULE_SLASH_CHEAP,
		       prefix, argv);
	refresh_index(&the_index, REFRESH_QUIET, &pathspec, NULL, NULL);

	seen = xcalloc(pathspec.nr, 1);

	for (i = 0; i < active_nr; i++) {
