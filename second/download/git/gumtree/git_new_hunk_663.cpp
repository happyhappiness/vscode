
	if (read_cache_preload(&pathspec) < 0)
		die(_("index file corrupt"));

	if (interactive) {
		char *old_index_env = NULL;
		hold_locked_index(&index_lock, LOCK_DIE_ON_ERROR);

		refresh_cache_or_die(refresh_flags);

		if (write_locked_index(&the_index, &index_lock, CLOSE_LOCK))
			die(_("unable to create temporary index"));

