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
		 * add/rm <file>', just 'git commit'.
		 */
		if (advice_resolve_conflict)
			die(_("You have not concluded your merge (MERGE_HEAD exists).\n"
				  "Please, commit your changes before you merge."));
		else
			die(_("You have not concluded your merge (MERGE_HEAD exists)."));
	}
	if (file_exists(git_path_cherry_pick_head())) {
		if (advice_resolve_conflict)
			die(_("You have not concluded your cherry-pick (CHERRY_PICK_HEAD exists).\n"
			    "Please, commit your changes before you merge."));
		else
			die(_("You have not concluded your cherry-pick (CHERRY_PICK_HEAD exists)."));
	}
