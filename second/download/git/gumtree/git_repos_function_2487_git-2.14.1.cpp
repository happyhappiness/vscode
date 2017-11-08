static enum path_treatment treat_one_path(struct dir_struct *dir,
					  struct untracked_cache_dir *untracked,
					  struct index_state *istate,
					  struct strbuf *path,
					  int baselen,
					  const struct pathspec *pathspec,
					  int dtype, struct dirent *de)
{
	int exclude;
	int has_path_in_index = !!index_file_exists(istate, path->buf, path->len, ignore_case);

	if (dtype == DT_UNKNOWN)
		dtype = get_dtype(de, istate, path->buf, path->len);

	/* Always exclude indexed files */
	if (dtype != DT_DIR && has_path_in_index)
		return path_none;

	/*
	 * When we are looking at a directory P in the working tree,
	 * there are three cases:
	 *
	 * (1) P exists in the index.  Everything inside the directory P in
	 * the working tree needs to go when P is checked out from the
	 * index.
	 *
	 * (2) P does not exist in the index, but there is P/Q in the index.
	 * We know P will stay a directory when we check out the contents
	 * of the index, but we do not know yet if there is a directory
	 * P/Q in the working tree to be killed, so we need to recurse.
	 *
	 * (3) P does not exist in the index, and there is no P/Q in the index
	 * to require P to be a directory, either.  Only in this case, we
	 * know that everything inside P will not be killed without
	 * recursing.
	 */
	if ((dir->flags & DIR_COLLECT_KILLED_ONLY) &&
	    (dtype == DT_DIR) &&
	    !has_path_in_index &&
	    (directory_exists_in_index(istate, path->buf, path->len) == index_nonexistent))
		return path_none;

	exclude = is_excluded(dir, istate, path->buf, &dtype);

	/*
	 * Excluded? If we don't explicitly want to show
	 * ignored files, ignore it
	 */
	if (exclude && !(dir->flags & (DIR_SHOW_IGNORED|DIR_SHOW_IGNORED_TOO)))
		return path_excluded;

	switch (dtype) {
	default:
		return path_none;
	case DT_DIR:
		strbuf_addch(path, '/');
		return treat_directory(dir, istate, untracked, path->buf, path->len,
				       baselen, exclude, pathspec);
	case DT_REG:
	case DT_LNK:
		return exclude ? path_excluded : path_untracked;
	}
}