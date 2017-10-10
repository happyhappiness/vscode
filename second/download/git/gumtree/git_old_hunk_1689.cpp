	if (read_cache() < 0)
		die(_("cannot read the index"));

	hold_locked_index(&index_lock, 1);
	add_remove_files(&partial);
	refresh_cache(REFRESH_QUIET);
	if (write_locked_index(&the_index, &index_lock, CLOSE_LOCK))
		die(_("unable to write new_index file"));

	hold_lock_file_for_update(&false_lock,
				  git_path("next-index-%"PRIuMAX,
					   (uintmax_t) getpid()),
