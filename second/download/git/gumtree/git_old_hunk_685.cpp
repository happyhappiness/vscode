		show_progress = 0;

	if (abort_current_merge) {
		int nargc = 2;
		const char *nargv[] = {"reset", "--merge", NULL};

		if (!file_exists(git_path_merge_head()))
			die(_("There is no merge to abort (MERGE_HEAD missing)."));

		/* Invoke 'git reset --merge' */
		ret = cmd_reset(nargc, nargv, prefix);
		goto done;
	}

	if (read_cache_unmerged())
		die_resolve_conflict("merge");

	if (file_exists(git_path_merge_head())) {
		/*
		 * There is no unmerged entry, don't advise 'git
