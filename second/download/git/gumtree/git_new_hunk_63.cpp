				   "%d lines add whitespace errors.",
				   whitespace_error),
				whitespace_error);
	}

	if (update_index) {
		if (write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
			die(_("Unable to write new index file"));
	}

	return !!errs;
}
