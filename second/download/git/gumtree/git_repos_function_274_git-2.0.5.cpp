void remove_marked_cache_entries(struct index_state *istate)
{
	struct cache_entry **ce_array = istate->cache;
	unsigned int i, j;

	for (i = j = 0; i < istate->cache_nr; i++) {
		if (ce_array[i]->ce_flags & CE_REMOVE) {
			remove_name_hash(istate, ce_array[i]);
			free(ce_array[i]);
		}
		else
			ce_array[j++] = ce_array[i];
	}
	istate->cache_changed = 1;
	istate->cache_nr = j;
}