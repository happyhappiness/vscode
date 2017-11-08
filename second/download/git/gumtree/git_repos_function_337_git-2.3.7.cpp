int read_index_unmerged(struct index_state *istate)
{
	int i;
	int unmerged = 0;

	read_index(istate);
	for (i = 0; i < istate->cache_nr; i++) {
		struct cache_entry *ce = istate->cache[i];
		struct cache_entry *new_ce;
		int size, len;

		if (!ce_stage(ce))
			continue;
		unmerged = 1;
		len = ce_namelen(ce);
		size = cache_entry_size(len);
		new_ce = xcalloc(1, size);
		memcpy(new_ce->name, ce->name, len);
		new_ce->ce_flags = create_ce_flags(0) | CE_CONFLICTED;
		new_ce->ce_namelen = len;
		new_ce->ce_mode = ce->ce_mode;
		if (add_index_entry(istate, new_ce, 0))
			return error("%s: cannot drop to stage #0",
				     new_ce->name);
	}
	return unmerged;
}