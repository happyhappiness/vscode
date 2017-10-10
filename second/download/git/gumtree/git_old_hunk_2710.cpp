		/* Turn "git add pathspec..." to "git add -A pathspec..." */
		addremove = 1;

	if (!show_only && ignore_missing)
		die(_("Option --ignore-missing can only be used together with --dry-run"));

	if ((0 < addremove_explicit || take_worktree_changes) && !argc) {
		static const char *whole[2] = { ":/", NULL };
		argc = 1;
		argv = whole;
	}

	add_new_files = !take_worktree_changes && !refresh_only;
	require_pathspec = !take_worktree_changes;

	hold_locked_index(&lock_file, 1);

	flags = ((verbose ? ADD_CACHE_VERBOSE : 0) |
		 (show_only ? ADD_CACHE_PRETEND : 0) |
		 (intent_to_add ? ADD_CACHE_INTENT : 0) |
