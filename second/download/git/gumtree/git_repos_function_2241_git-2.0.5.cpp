static int check_ok_to_remove(const char *name, int len, int dtype,
			      const struct cache_entry *ce, struct stat *st,
			      enum unpack_trees_error_types error_type,
			      struct unpack_trees_options *o)
{
	const struct cache_entry *result;

	/*
	 * It may be that the 'lstat()' succeeded even though
	 * target 'ce' was absent, because there is an old
	 * entry that is different only in case..
	 *
	 * Ignore that lstat() if it matches.
	 */
	if (ignore_case && icase_exists(o, name, len, st))
		return 0;

	if (o->dir &&
	    is_excluded(o->dir, name, &dtype))
		/*
		 * ce->name is explicitly excluded, so it is Ok to
		 * overwrite it.
		 */
		return 0;
	if (S_ISDIR(st->st_mode)) {
		/*
		 * We are checking out path "foo" and
		 * found "foo/." in the working tree.
		 * This is tricky -- if we have modified
		 * files that are in "foo/" we would lose
		 * them.
		 */
		if (verify_clean_subdirectory(ce, error_type, o) < 0)
			return -1;
		return 0;
	}

	/*
	 * The previous round may already have decided to
	 * delete this path, which is in a subdirectory that
	 * is being replaced with a blob.
	 */
	result = index_file_exists(&o->result, name, len, 0);
	if (result) {
		if (result->ce_flags & CE_REMOVE)
			return 0;
	}

	return o->gently ? -1 :
		add_rejected_path(o, error_type, name);
}