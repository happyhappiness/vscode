int fill_directory(struct dir_struct *dir, const struct pathspec *pathspec)
{
	const char *prefix;
	size_t prefix_len;

	/*
	 * Calculate common prefix for the pathspec, and
	 * use that to optimize the directory walk
	 */
	prefix_len = common_prefix_len(pathspec);
	prefix = prefix_len ? pathspec->items[0].match : "";

	/* Read the directory and prune it */
	read_directory(dir, prefix, prefix_len, pathspec);

	return prefix_len;
}