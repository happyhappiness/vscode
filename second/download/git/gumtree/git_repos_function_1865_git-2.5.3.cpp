static enum exist_status directory_exists_in_index_icase(const char *dirname, int len)
{
	const struct cache_entry *ce = cache_dir_exists(dirname, len);
	unsigned char endchar;

	if (!ce)
		return index_nonexistent;
	endchar = ce->name[len];

	/*
	 * The cache_entry structure returned will contain this dirname
	 * and possibly additional path components.
	 */
	if (endchar == '/')
		return index_directory;

	/*
	 * If there are no additional path components, then this cache_entry
	 * represents a submodule.  Submodules, despite being directories,
	 * are stored in the cache without a closing slash.
	 */
	if (!endchar && S_ISGITLINK(ce->ce_mode))
		return index_gitdir;

	/* This should never be hit, but it exists just in case. */
	return index_nonexistent;
}