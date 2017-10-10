		exit(1);

	discard_cache();
	if (read_cache() < 0)
		die(_("cannot read the index"));

	hold_locked_index(&index_lock, LOCK_DIE_ON_ERROR);
	add_remove_files(&partial);
	refresh_cache(REFRESH_QUIET);
	update_main_cache_tree(WRITE_TREE_SILENT);
	if (write_locked_index(&the_index, &index_lock, CLOSE_LOCK))
		die(_("unable to write new_index file"));

