	 *
	 * The caller should run hooks on the real index,
	 * and create commit from the_index.
	 * We still need to refresh the index here.
	 */
	if (!only && !pathspec.nr) {
		hold_locked_index(&index_lock, 1);
		refresh_cache_or_die(refresh_flags);
		if (active_cache_changed) {
			update_main_cache_tree(WRITE_TREE_SILENT);
			if (write_locked_index(&the_index, &index_lock,
					       COMMIT_LOCK))
				die(_("unable to write new_index file"));
		} else {
			rollback_lock_file(&index_lock);
		}
		commit_style = COMMIT_AS_IS;
		return get_index_file();
