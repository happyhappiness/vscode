int has_symlink_leading_path(const char *name, int len)
{
	return threaded_has_symlink_leading_path(&default_cache, name, len);
}