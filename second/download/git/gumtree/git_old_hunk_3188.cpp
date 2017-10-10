		 * be shared with the_index.cache[]. So yeah we're
		 * leaking a bit here.
		 */
		the_index.split_index = NULL;
		the_index.cache_changed |= SOMETHING_CHANGED;
	}
	if (untracked_cache > 0) {
		struct untracked_cache *uc;

		if (untracked_cache < 2) {
			setup_work_tree();
			if (!test_if_untracked_cache_is_supported())
				return 1;
		}
		if (!the_index.untracked) {
			uc = xcalloc(1, sizeof(*uc));
			strbuf_init(&uc->ident, 100);
			uc->exclude_per_dir = ".gitignore";
			/* should be the same flags used by git-status */
			uc->dir_flags = DIR_SHOW_OTHER_DIRECTORIES | DIR_HIDE_EMPTY_DIRECTORIES;
			the_index.untracked = uc;
		}
		add_untracked_ident(the_index.untracked);
		the_index.cache_changed |= UNTRACKED_CHANGED;
	} else if (!untracked_cache && the_index.untracked) {
		the_index.untracked = NULL;
		the_index.cache_changed |= UNTRACKED_CHANGED;
	}

	if (active_cache_changed) {
		if (newfd < 0) {
			if (refresh_args.flags & REFRESH_QUIET)
				exit(128);
