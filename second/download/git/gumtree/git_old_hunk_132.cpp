			free((char *)p);
		}
		strbuf_release(&nbuf);
		strbuf_release(&buf);
	}

	if (active_cache_changed) {
		if (newfd < 0) {
			if (refresh_args.flags & REFRESH_QUIET)
				exit(128);
			unable_to_lock_index_die(get_index_file(), lock_error);
		}
		if (write_cache(newfd, active_cache, active_nr) ||
		    commit_locked_index(lock_file))
			die("Unable to write new index file");
	}

	rollback_lock_file(lock_file);

	return has_errors ? 1 : 0;
