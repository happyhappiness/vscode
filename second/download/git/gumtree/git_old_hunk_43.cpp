		config_filename = filename_buf = git_pathdup("config");

	/*
	 * The lock serves a purpose in addition to locking: the new
	 * contents of .git/config will be written into it.
	 */
	lock = xcalloc(sizeof(struct lock_file), 1);
	fd = hold_lock_file_for_update(lock, config_filename, 0);
	if (fd < 0) {
		error("could not lock config file %s: %s", config_filename, strerror(errno));
		free(store.key);
		ret = CONFIG_NO_LOCK;
		goto out_free;
