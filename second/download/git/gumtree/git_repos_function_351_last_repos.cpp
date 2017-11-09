static int check_file_directory_conflict(struct index_state *istate,
					 const struct cache_entry *ce,
					 int pos, int ok_to_replace)
{
	int retval;

	/*
	 * When ce is an "I am going away" entry, we allow it to be added
	 */
	if (ce->ce_flags & CE_REMOVE)
		return 0;

	/*
	 * We check if the path is a sub-path of a subsequent pathname
	 * first, since removing those will not change the position
	 * in the array.
	 */
	retval = has_file_name(istate, ce, pos, ok_to_replace);

	/*
	 * Then check if the path might have a clashing sub-directory
	 * before it.
	 */
	return retval + has_dir_name(istate, ce, pos, ok_to_replace);
}