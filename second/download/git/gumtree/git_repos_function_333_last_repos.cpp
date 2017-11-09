int remove_index_entry_at(struct index_state *istate, int pos)
{
	struct cache_entry *ce = istate->cache[pos];

	record_resolve_undo(istate, ce);
	remove_name_hash(istate, ce);
	save_or_free_index_entry(istate, ce);
	istate->cache_changed |= CE_ENTRY_REMOVED;
	istate->cache_nr--;
	if (pos >= istate->cache_nr)
		return 0;
	MOVE_ARRAY(istate->cache + pos, istate->cache + pos + 1,
		   istate->cache_nr - pos);
	return 1;
}