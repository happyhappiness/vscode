static struct cache_entry *refresh_cache_entry(struct cache_entry *ce,
					       unsigned int options)
{
	return refresh_cache_ent(&the_index, ce, options, NULL, NULL);
}