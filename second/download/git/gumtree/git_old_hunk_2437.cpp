	 * We still need to refresh the index here.
	 */
	if (!only && !pathspec.nr) {
		hold_locked_index(&index_lock, 1);
		refresh_cache_or_die(refresh_flags);
		if (active_cache_changed
		    || !cache_tree_fully_valid(active_cache_tree)) {
			update_main_cache_tree(WRITE_TREE_SILENT);
			active_cache_changed = 1;
		}
		if (active_cache_changed) {
			if (write_locked_index(&the_index, &index_lock,
					       COMMIT_LOCK))
				die(_("unable to write new_index file"));
		} else {
			rollback_lock_file(&index_lock);
