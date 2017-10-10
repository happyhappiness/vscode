				   "%d lines add whitespace errors.",
				   whitespace_error),
				whitespace_error);
	}

	if (update_index) {
		if (write_cache(newfd, active_cache, active_nr) ||
		    commit_locked_index(&lock_file))
			die(_("Unable to write new index file"));
	}

	return !!errs;
}
