		if (whence == FROM_MERGE)
			die(_("cannot do a partial commit during a merge."));
		else if (whence == FROM_CHERRY_PICK)
			die(_("cannot do a partial commit during a cherry-pick."));
	}

	string_list_init(&partial, 1);
	if (list_paths(&partial, !current_head ? NULL : "HEAD", prefix, &pathspec))
		exit(1);

	discard_cache();
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
				  LOCK_DIE_ON_ERROR);

	create_base_index(current_head);
	add_remove_files(&partial);
	refresh_cache(REFRESH_QUIET);

	if (write_locked_index(&the_index, &false_lock, CLOSE_LOCK))
		die(_("unable to write temporary index file"));

	discard_cache();
	read_cache_from(false_lock.filename);

	return false_lock.filename;
