		return 0;
	}

	if (read_cache() < 0)
		die(_("index file corrupt"));

	/*
	 * Check the "pathspec '%s' did not match any files" block
	 * below before enabling new magic.
	 */
	parse_pathspec(&pathspec, 0,
		       PATHSPEC_PREFER_FULL |
		       PATHSPEC_SYMLINK_LEADING_PATH |
		       PATHSPEC_STRIP_SUBMODULE_SLASH_EXPENSIVE,
		       prefix, argv);

	if (add_new_files) {
		int baselen;

		/* Set up the default git porcelain excludes */
		memset(&dir, 0, sizeof(dir));
		if (!ignored_too) {
			dir.flags |= DIR_COLLECT_IGNORED;
			setup_standard_excludes(&dir);
		}

		/* This picks up the paths that are not tracked */
		baselen = fill_directory(&dir, &pathspec);
		if (pathspec.nr)
			seen = prune_directory(&dir, &pathspec, baselen);
	}

	if (refresh_only) {
		refresh(verbose, &pathspec);
