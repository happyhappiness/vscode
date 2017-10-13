int git_config_set_multivar_in_file(const char *config_filename,
				const char *key, const char *value,
				const char *value_regex, int multi_replace)
{
	int fd = -1, in_fd;
	int ret;
	struct lock_file *lock = NULL;
	char *filename_buf = NULL;

	/* parse-key returns negative; flip the sign to feed exit(3) */
	ret = 0 - git_config_parse_key(key, &store.key, &store.baselen);
	if (ret)
		goto out_free;

	store.multi_replace = multi_replace;

	if (!config_filename)
		config_filename = filename_buf = git_pathdup("config");

	/*
	 * The lock serves a purpose in addition to locking: the new
	 * contents of .git/config will be written into it.
	 */
	lock = xcalloc(1, sizeof(struct lock_file));
	fd = hold_lock_file_for_update(lock, config_filename, 0);
	if (fd < 0) {
		error("could not lock config file %s: %s", config_filename, strerror(errno));
		free(store.key);
		ret = CONFIG_NO_LOCK;
		goto out_free;
	}

	/*
	 * If .git/config does not exist yet, write a minimal version.
	 */
	in_fd = open(config_filename, O_RDONLY);
	if ( in_fd < 0 ) {
		free(store.key);

		if ( ENOENT != errno ) {
			error("opening %s: %s", config_filename,
			      strerror(errno));
			ret = CONFIG_INVALID_FILE; /* same as "invalid config file" */
			goto out_free;
		}
		/* if nothing to unset, error out */
		if (value == NULL) {
			ret = CONFIG_NOTHING_SET;
			goto out_free;
		}

		store.key = (char *)key;
		if (!store_write_section(fd, key) ||
		    !store_write_pair(fd, key, value))
			goto write_err_out;
	} else {
		struct stat st;
		char *contents;
		size_t contents_sz, copy_begin, copy_end;
		int i, new_line = 0;

		if (value_regex == NULL)
			store.value_regex = NULL;
		else {
			if (value_regex[0] == '!') {
				store.do_not_match = 1;
				value_regex++;
			} else
				store.do_not_match = 0;

			store.value_regex = (regex_t*)xmalloc(sizeof(regex_t));
			if (regcomp(store.value_regex, value_regex,
					REG_EXTENDED)) {
				error("invalid pattern: %s", value_regex);
				free(store.value_regex);
				ret = CONFIG_INVALID_PATTERN;
				goto out_free;
			}
		}

		ALLOC_GROW(store.offset, 1, store.offset_alloc);
		store.offset[0] = 0;
		store.state = START;
		store.seen = 0;

		/*
		 * After this, store.offset will contain the *end* offset
		 * of the last match, or remain at 0 if no match was found.
		 * As a side effect, we make sure to transform only a valid
		 * existing config file.
		 */
		if (git_config_from_file(store_aux, config_filename, NULL)) {
			error("invalid config file %s", config_filename);
			free(store.key);
			if (store.value_regex != NULL) {
				regfree(store.value_regex);
				free(store.value_regex);
			}
			ret = CONFIG_INVALID_FILE;
			goto out_free;
		}

		free(store.key);
		if (store.value_regex != NULL) {
			regfree(store.value_regex);
			free(store.value_regex);
		}

		/* if nothing to unset, or too many matches, error out */
		if ((store.seen == 0 && value == NULL) ||
				(store.seen > 1 && multi_replace == 0)) {
			ret = CONFIG_NOTHING_SET;
			goto out_free;
		}

		fstat(in_fd, &st);
		contents_sz = xsize_t(st.st_size);
		contents = xmmap(NULL, contents_sz, PROT_READ,
			MAP_PRIVATE, in_fd, 0);
		close(in_fd);

		if (chmod(lock->filename, st.st_mode & 07777) < 0) {
			error("chmod on %s failed: %s",
				lock->filename, strerror(errno));
			ret = CONFIG_NO_WRITE;
			goto out_free;
		}

		if (store.seen == 0)
			store.seen = 1;

		for (i = 0, copy_begin = 0; i < store.seen; i++) {
			if (store.offset[i] == 0) {
				store.offset[i] = copy_end = contents_sz;
			} else if (store.state != KEY_SEEN) {
				copy_end = store.offset[i];
			} else
				copy_end = find_beginning_of_line(
					contents, contents_sz,
					store.offset[i]-2, &new_line);

			if (copy_end > 0 && contents[copy_end-1] != '\n')
				new_line = 1;

			/* write the first part of the config */
			if (copy_end > copy_begin) {
				if (write_in_full(fd, contents + copy_begin,
						  copy_end - copy_begin) <
				    copy_end - copy_begin)
					goto write_err_out;
				if (new_line &&
				    write_str_in_full(fd, "\n") != 1)
					goto write_err_out;
			}
			copy_begin = store.offset[i];
		}

		/* write the pair (value == NULL means unset) */
		if (value != NULL) {
			if (store.state == START) {
				if (!store_write_section(fd, key))
					goto write_err_out;
			}
			if (!store_write_pair(fd, key, value))
				goto write_err_out;
		}

		/* write the rest of the config */
		if (copy_begin < contents_sz)
			if (write_in_full(fd, contents + copy_begin,
					  contents_sz - copy_begin) <
			    contents_sz - copy_begin)
				goto write_err_out;

		munmap(contents, contents_sz);
	}

	if (commit_lock_file(lock) < 0) {
		error("could not commit config file %s", config_filename);
		ret = CONFIG_NO_WRITE;
		goto out_free;
	}

	/*
	 * lock is committed, so don't try to roll it back below.
	 * NOTE: Since lockfile.c keeps a linked list of all created
	 * lock_file structures, it isn't safe to free(lock).  It's
	 * better to just leave it hanging around.
	 */
	lock = NULL;
	ret = 0;

out_free:
	if (lock)
		rollback_lock_file(lock);
	free(filename_buf);
	return ret;

write_err_out:
	ret = write_error(lock->filename);
	goto out_free;

}