static enum exist_status directory_exists_in_index_icase(const char *dirname, int len)
{
	struct cache_entry *ce;

	if (cache_dir_exists(dirname, len))
		return index_directory;

	ce = cache_file_exists(dirname, len, ignore_case);
	if (ce && S_ISGITLINK(ce->ce_mode))
		return index_gitdir;

	return index_nonexistent;
}