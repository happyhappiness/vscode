static inline void lazy_update_dir_ref_counts(
	struct index_state *istate,
	struct lazy_entry *lazy_entries)
{
	int k;

	for (k = 0; k < istate->cache_nr; k++) {
		if (lazy_entries[k].dir)
			lazy_entries[k].dir->nr++;
	}
}