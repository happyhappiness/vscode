static struct ref_dir *get_packed_ref_dir(struct packed_ref_cache *packed_ref_cache)
{
	return get_ref_dir(packed_ref_cache->cache->root);
}