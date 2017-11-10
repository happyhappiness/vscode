int read_directory(struct dir_struct *dir, const char *path, int len, const struct pathspec *pathspec)
{
	struct path_simplify *simplify;
	struct untracked_cache_dir *untracked;

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
	untracked = validate_untracked_cache(dir, len, pathspec);
	if (!untracked)
		/*
		 * make sure untracked cache code path is disabled,
		 * e.g. prep_exclude()
		 */
		dir->untracked = NULL;
	if (!len || treat_leading_path(dir, path, len, simplify))
		read_directory_recursive(dir, path, len, untracked, 0, simplify);
	free_simplify(simplify);
	qsort(dir->entries, dir->nr, sizeof(struct dir_entry *), cmp_name);
	qsort(dir->ignored, dir->ignored_nr, sizeof(struct dir_entry *), cmp_name);
	if (dir->untracked) {
		static struct trace_key trace_untracked_stats = TRACE_KEY_INIT(UNTRACKED_STATS);
		trace_printf_key(&trace_untracked_stats,
				 "node creation: %u\n"
				 "gitignore invalidation: %u\n"
				 "directory invalidation: %u\n"
				 "opendir: %u\n",
				 dir->untracked->dir_created,
				 dir->untracked->gitignore_invalidated,
				 dir->untracked->dir_invalidated,
				 dir->untracked->dir_opened);
		if (dir->untracked == the_index.untracked &&
		    (dir->untracked->dir_opened ||
		     dir->untracked->gitignore_invalidated ||
		     dir->untracked->dir_invalidated))
			the_index.cache_changed |= UNTRACKED_CHANGED;
		if (dir->untracked != the_index.untracked) {
			free(dir->untracked);
			dir->untracked = NULL;
		}
	}
	return dir->nr;
}