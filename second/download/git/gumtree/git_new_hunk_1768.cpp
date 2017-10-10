	}

	if (active_cache_changed) {
		if (newfd < 0) {
			if (refresh_args.flags & REFRESH_QUIET)
				exit(128);
			unable_to_lock_die(get_index_file(), lock_error);
		}
		if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
			die("Unable to write new index file");
	}

	rollback_lock_file(lock_file);
