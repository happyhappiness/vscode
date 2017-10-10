	char buf[1024];
	FILE *config_file;
	struct stat st;

	if (new_name && !section_name_is_ok(new_name)) {
		ret = error("invalid section name: %s", new_name);
		goto out_no_rollback;
	}

	if (!config_filename)
		config_filename = filename_buf = git_pathdup("config");

	lock = xcalloc(1, sizeof(struct lock_file));
