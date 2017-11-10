int read_directory(struct dir_struct *dir, const char *path, int len, const struct pathspec *pathspec)
{
	struct path_simplify *simplify;

	/*
	 * Check out create_simplify()
	 */
	if (pathspec)
		GUARD_PATHSPEC(pathspec,
			       PATHSPEC_FROMTOP |
			       PATHSPEC_MAXDEPTH |
			       PATHSPEC_LITERAL |
			       PATHSPEC_GLOB |
			       PATHSPEC_ICASE |
			       PATHSPEC_EXCLUDE);

	if (has_symlink_leading_path(path, len))
		return dir->nr;

	/*
	 * exclude patterns are treated like positive ones in
	 * create_simplify. Usually exclude patterns should be a
	 * subset of positive ones, which has no impacts on
	 * create_simplify().
	 */
	simplify = create_simplify(pathspec ? pathspec->_raw : NULL);
	if (!len || treat_leading_path(dir, path, len, simplify))
		read_directory_recursive(dir, path, len, 0, simplify);
	free_simplify(simplify);
	qsort(dir->entries, dir->nr, sizeof(struct dir_entry *), cmp_name);
	qsort(dir->ignored, dir->ignored_nr, sizeof(struct dir_entry *), cmp_name);
	return dir->nr;
}