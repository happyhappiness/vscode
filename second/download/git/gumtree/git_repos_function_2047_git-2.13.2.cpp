int raceproof_create_file(const char *path, create_file_fn fn, void *cb)
{
	/*
	 * The number of times we will try to remove empty directories
	 * in the way of path. This is only 1 because if another
	 * process is racily creating directories that conflict with
	 * us, we don't want to fight against them.
	 */
	int remove_directories_remaining = 1;

	/*
	 * The number of times that we will try to create the
	 * directories containing path. We are willing to attempt this
	 * more than once, because another process could be trying to
	 * clean up empty directories at the same time as we are
	 * trying to create them.
	 */
	int create_directories_remaining = 3;

	/* A scratch copy of path, filled lazily if we need it: */
	struct strbuf path_copy = STRBUF_INIT;

	int ret, save_errno;

	/* Sanity check: */
	assert(*path);

retry_fn:
	ret = fn(path, cb);
	save_errno = errno;
	if (!ret)
		goto out;

	if (errno == EISDIR && remove_directories_remaining-- > 0) {
		/*
		 * A directory is in the way. Maybe it is empty; try
		 * to remove it:
		 */
		if (!path_copy.len)
			strbuf_addstr(&path_copy, path);

		if (!remove_dir_recursively(&path_copy, REMOVE_DIR_EMPTY_ONLY))
			goto retry_fn;
	} else if (errno == ENOENT && create_directories_remaining-- > 0) {
		/*
		 * Maybe the containing directory didn't exist, or
		 * maybe it was just deleted by a process that is
		 * racing with us to clean up empty directories. Try
		 * to create it:
		 */
		enum scld_error scld_result;

		if (!path_copy.len)
			strbuf_addstr(&path_copy, path);

		do {
			scld_result = safe_create_leading_directories(path_copy.buf);
			if (scld_result == SCLD_OK)
				goto retry_fn;
		} while (scld_result == SCLD_VANISHED && create_directories_remaining-- > 0);
	}

out:
	strbuf_release(&path_copy);
	errno = save_errno;
	return ret;
}