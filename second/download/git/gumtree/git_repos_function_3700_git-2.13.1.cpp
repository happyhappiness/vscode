void move_cache_to_base_index(struct index_state *istate)
{
	struct split_index *si = istate->split_index;
	int i;

	/*
	 * do not delete old si->base, its index entries may be shared
	 * with istate->cache[]. Accept a bit of leaking here because
	 * this code is only used by short-lived update-index.
	 */
	si->base = xcalloc(1, sizeof(*si->base));
	si->base->version = istate->version;
	/* zero timestamp disables racy test in ce_write_index() */
	si->base->timestamp = istate->timestamp;
	ALLOC_GROW(si->base->cache, istate->cache_nr, si->base->cache_alloc);
	si->base->cache_nr = istate->cache_nr;
	COPY_ARRAY(si->base->cache, istate->cache, istate->cache_nr);
	mark_base_index_entries(si->base);
	for (i = 0; i < si->base->cache_nr; i++)
		si->base->cache[i]->ce_flags &= ~CE_UPDATE_IN_BASE;
}