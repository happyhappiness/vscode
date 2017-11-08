static void replace_index_entry(struct index_state *istate, int nr, struct cache_entry *ce)
{
	struct cache_entry *old = istate->cache[nr];

	replace_index_entry_in_base(istate, old, ce);
	remove_name_hash(istate, old);
	free(old);
	set_index_entry(istate, nr, ce);
	ce->ce_flags |= CE_UPDATE_IN_BASE;
	istate->cache_changed |= CE_ENTRY_CHANGED;
}