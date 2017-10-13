int git_config_rename_section_in_file(const char *config_filename,
				      const char *old_name, const char *new_name)
{
	int ret = 0, remove = 0;
	char *filename_buf = NULL;
	struct lock_file *lock;
	int out_fd;
	char buf[1024];
	FILE *config_file;
	struct stat st;

	if (new_name && !section_name_is_ok(new_name)) {
		ret = error("invalid section name: %s", new_name);
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

	if (!(config_file = fopen(config_filename, "rb"))) {
		/* no config file means nothing to rename, no error */
		goto unlock_and_out;
	}

	fstat(fileno(config_file), &st);

	if (chmod(get_lock_file_path(lock), st.st_mode & 07777) < 0) {
		ret = error("chmod on %s failed: %s",
			    get_lock_file_path(lock), strerror(errno));
		goto out;
	}

	while (fgets(buf, sizeof(buf), config_file)) {
		int i;
		int length;
		char *output = buf;
		for (i = 0; buf[i] && isspace(buf[i]); i++)
			; /* do nothing */
		if (buf[i] == '[') {
			/* it's a section */
			int offset = section_name_match(&buf[i], old_name);
			if (offset > 0) {
				ret++;
				if (new_name == NULL) {
					remove = 1;
					continue;
				}
				store.baselen = strlen(new_name);
				if (!store_write_section(out_fd, new_name)) {
					ret = write_error(get_lock_file_path(lock));
					goto out;
				}
				/*
				 * We wrote out the new section, with
				 * a newline, now skip the old
				 * section's length
				 */
				output += offset + i;
				if (strlen(output) > 0) {
					/*
					 * More content means there's
					 * a declaration to put on the
					 * next line; indent with a
					 * tab
					 */
					output -= 1;
					output[0] = '\t';
				}
			}
			remove = 0;
		}
		if (remove)
			continue;
		length = strlen(output);
		if (write_in_full(out_fd, output, length) != length) {
			ret = write_error(get_lock_file_path(lock));
			goto out;
		}
	}
	fclose(config_file);
unlock_and_out:
	if (commit_lock_file(lock) < 0)
		ret = error("could not commit config file %s", config_filename);
out:
	free(filename_buf);
	return ret;
}