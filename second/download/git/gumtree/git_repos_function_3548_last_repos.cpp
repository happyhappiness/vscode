static int threaded_check_leading_path(struct cache_def *cache, const char *name, int len)
{
	int flags;
	int match_len = lstat_cache_matchlen(cache, name, len, &flags,
			   FL_SYMLINK|FL_NOENT|FL_DIR, USE_ONLY_LSTAT);
	if (flags & FL_NOENT)
		return 0;
	else if (flags & FL_DIR)
		return -1;
	else
		return match_len;
}