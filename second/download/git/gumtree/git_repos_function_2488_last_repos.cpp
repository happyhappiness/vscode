static enum exist_status directory_exists_in_index_icase(struct index_state *istate,
							 const char *dirname, int len)
{
	struct cache_entry *ce;

	if (index_dir_exists(istate, dirname, len))
		return index_directory;

	ce = index_file_exists(istate, dirname, len, ignore_case);
	if (ce && S_ISGITLINK(ce->ce_mode))
		return index_gitdir;

	return index_nonexistent;
}