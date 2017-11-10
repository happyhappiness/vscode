static inline void cache_def_clear(struct cache_def *cache)
{
	strbuf_release(&cache->path);
}