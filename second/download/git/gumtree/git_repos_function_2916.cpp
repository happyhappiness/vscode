int has_dirs_only_path(const char *name, int len, int prefix_len)
{
	return threaded_has_dirs_only_path(&default_cache, name, len, prefix_len);
}