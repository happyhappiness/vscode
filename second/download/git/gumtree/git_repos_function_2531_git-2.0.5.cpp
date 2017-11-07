static inline void reset_lstat_cache(struct cache_def *cache)
{
	cache->path[0] = '\0';
	cache->len = 0;
	cache->flags = 0;
	/*
	 * The track_flags and prefix_len_stat_func members is only
	 * set by the safeguard rule inside lstat_cache()
	 */
}