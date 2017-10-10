
	if (read_cache_preload(&pathspec) < 0)
		die(_("index file corrupt"));

	if (interactive) {
		char *old_index_env = NULL;
		hold_locked_index(&index_lock, 1);

		refresh_cache_or_die(refresh_flags);

		if (write_locked_index(&the_index, &index_lock, CLOSE_LOCK))
			die(_("unable to create temporary index"));

		old_index_env = getenv(INDEX_ENVIRONMENT);
		setenv(INDEX_ENVIRONMENT, index_lock.filename, 1);

		if (interactive_add(argc, argv, prefix, patch_interactive) != 0)
