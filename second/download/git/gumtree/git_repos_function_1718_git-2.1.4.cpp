int fill_directory(struct dir_struct *dir, const struct pathspec *pathspec)
{
	size_t len;

	/*
	 * Calculate common prefix for the pathspec, and
	 * use that to optimize the directory walk
	 */
	len = common_prefix_len(pathspec);

	/* Read the directory and prune it */
	read_directory(dir, pathspec->nr ? pathspec->_raw[0] : "", len, pathspec);
	return len;
}