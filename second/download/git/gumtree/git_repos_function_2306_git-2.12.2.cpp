int read_directory(struct dir_struct *dir, const char *path,
		   int len, const struct pathspec *pathspec)
{
	struct untracked_cache_dir *untracked;

	if (has_symlink_leading_path(path, len))
		return dir->nr;

	untracked = validate_untracked_cache(dir, len, pathspec);
	if (!untracked)
		/*
		 * make sure untracked cache code path is disabled,
		 * e.g. prep_exclude()
		 */
		dir->untracked = NULL;
	if (!len || treat_leading_path(dir, path, len, pathspec))
		read_directory_recursive(dir, path, len, untracked, 0, pathspec);
	QSORT(dir->entries, dir->nr, cmp_name);
	QSORT(dir->ignored, dir->ignored_nr, cmp_name);
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