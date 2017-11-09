static enum path_treatment treat_directory(struct dir_struct *dir,
	struct index_state *istate,
	struct untracked_cache_dir *untracked,
	const char *dirname, int len, int baselen, int exclude,
	const struct pathspec *pathspec)
{
	/* The "len-1" is to strip the final '/' */
	switch (directory_exists_in_index(istate, dirname, len-1)) {
	case index_directory:
		return path_recurse;

	case index_gitdir:
		return path_none;

	case index_nonexistent:
		if (dir->flags & DIR_SHOW_OTHER_DIRECTORIES)
			break;
		if (!(dir->flags & DIR_NO_GITLINKS)) {
			unsigned char sha1[20];
			if (resolve_gitlink_ref(dirname, "HEAD", sha1) == 0)
				return path_untracked;
		}
		return path_recurse;
	}

	/* This is the "show_other_directories" case */

	if (!(dir->flags & DIR_HIDE_EMPTY_DIRECTORIES))
		return exclude ? path_excluded : path_untracked;

	untracked = lookup_untracked(dir->untracked, untracked,
				     dirname + baselen, len - baselen);
	return read_directory_recursive(dir, istate, dirname, len,
					untracked, 1, pathspec);
}