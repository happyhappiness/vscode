void free_ref_cache(struct ref_cache *cache)
{
	free_ref_entry(cache->root);
	free(cache);
}