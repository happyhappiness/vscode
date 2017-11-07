static inline void reset_lstat_cache(struct cache_def *cache)
{
	strbuf_reset(&cache->path);
	cache->flags = 0;
	/*
	 * The track_flags and prefix_len_stat_func members is only
	 * set by the safeguard rule inside lstat_cache()
	 */
}