int cache_tree_update(struct index_state *istate, int flags)
{
	struct cache_tree *it = istate->cache_tree;
	struct cache_entry **cache = istate->cache;
	int entries = istate->cache_nr;
	int skip, i = verify_cache(cache, entries, flags);

	if (i)
		return i;
	i = update_one(it, cache, entries, "", 0, &skip, flags);
	if (i < 0)
		return i;
	istate->cache_changed |= CACHE_TREE_CHANGED;
	return 0;
}