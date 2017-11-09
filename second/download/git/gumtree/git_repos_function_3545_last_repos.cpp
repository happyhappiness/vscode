int threaded_has_symlink_leading_path(struct cache_def *cache, const char *name, int len)
{
	return lstat_cache(cache, name, len, FL_SYMLINK|FL_DIR, USE_ONLY_LSTAT) & FL_SYMLINK;
}