		goto out;
	}

	if (!config_filename)
		config_filename = filename_buf = git_pathdup("config");

	lock = xcalloc(1, sizeof(struct lock_file));
	out_fd = hold_lock_file_for_update(lock, config_filename, 0);
	if (out_fd < 0) {
		ret = error("could not lock config file %s", config_filename);
		goto out;
	}

