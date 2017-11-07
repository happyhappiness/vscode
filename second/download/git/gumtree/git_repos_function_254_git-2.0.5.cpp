static void replace_index_entry(struct index_state *istate, int nr, struct cache_entry *ce)
{
	struct cache_entry *old = istate->cache[nr];

	remove_name_hash(istate, old);
	free(old);
	set_index_entry(istate, nr, ce);
	istate->cache_changed = 1;
}