void unmerge_marked_index(struct index_state *istate)
{
	int i;

	if (!istate->resolve_undo)
		return;

	for (i = 0; i < istate->cache_nr; i++) {
		const struct cache_entry *ce = istate->cache[i];
		if (ce->ce_flags & CE_MATCHED)
			i = unmerge_index_entry_at(istate, i);
	}
}