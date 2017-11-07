int cache_tree_update(struct cache_tree *it,
		      const struct cache_entry * const *cache,
		      int entries,
		      int flags)
{
	int i, skip;
	i = verify_cache(cache, entries, flags);
	if (i)
		return i;
	i = update_one(it, cache, entries, "", 0, &skip, flags);
	if (i < 0)
		return i;
	return 0;
}