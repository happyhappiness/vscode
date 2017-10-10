		refresh_cache_or_die(refresh_flags);

		if (write_locked_index(&the_index, &index_lock, CLOSE_LOCK))
			die(_("unable to create temporary index"));

		old_index_env = getenv(INDEX_ENVIRONMENT);
		setenv(INDEX_ENVIRONMENT, index_lock.filename, 1);

		if (interactive_add(argc, argv, prefix, patch_interactive) != 0)
			die(_("interactive add failed"));

		if (old_index_env && *old_index_env)
			setenv(INDEX_ENVIRONMENT, old_index_env, 1);
		else
			unsetenv(INDEX_ENVIRONMENT);

		discard_cache();
		read_cache_from(index_lock.filename);

		commit_style = COMMIT_NORMAL;
		return index_lock.filename;
	}

	/*
	 * Non partial, non as-is commit.
	 *
	 * (1) get the real index;
