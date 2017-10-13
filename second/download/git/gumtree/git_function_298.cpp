static int check_to_create(struct apply_state *state,
			   const char *new_name,
			   int ok_if_exists)
{
	struct stat nst;

	if (state->check_index &&
	    cache_name_pos(new_name, strlen(new_name)) >= 0 &&
	    !ok_if_exists)
		return EXISTS_IN_INDEX;
	if (state->cached)
		return 0;

	if (!lstat(new_name, &nst)) {
		if (S_ISDIR(nst.st_mode) || ok_if_exists)
			return 0;
		/*
		 * A leading component of new_name might be a symlink
		 * that is going to be removed with this patch, but
		 * still pointing at somewhere that has the path.
		 * In such a case, path "new_name" does not exist as
		 * far as git is concerned.
		 */
		if (has_symlink_leading_path(new_name, strlen(new_name)))
			return 0;

		return EXISTS_IN_WORKTREE;
	} else if ((errno != ENOENT) && (errno != ENOTDIR)) {
		return error("%s: %s", new_name, strerror(errno));
	}
	return 0;
}