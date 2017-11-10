static int process_path(const char *path)
{
	int pos, len;
	struct stat st;
	const struct cache_entry *ce;

	len = strlen(path);
	if (has_symlink_leading_path(path, len))
		return error("'%s' is beyond a symbolic link", path);

	pos = cache_name_pos(path, len);
	ce = pos < 0 ? NULL : active_cache[pos];
	if (ce && ce_skip_worktree(ce)) {
		/*
		 * working directory version is assumed "good"
		 * so updating it does not make sense.
		 * On the other hand, removing it from index should work
		 */
		if (allow_remove && remove_file_from_cache(path))
			return error("%s: cannot remove from the index", path);
		return 0;
	}

	/*
	 * First things first: get the stat information, to decide
	 * what to do about the pathname!
	 */
	if (lstat(path, &st) < 0)
		return process_lstat_error(path, errno);

	if (S_ISDIR(st.st_mode))
		return process_directory(path, len, &st);

	return add_one_path(ce, path, len, &st);
}