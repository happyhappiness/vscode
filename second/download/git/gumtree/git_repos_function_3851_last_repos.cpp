void prepare_to_write_split_index(struct index_state *istate)
{
	struct split_index *si = init_split_index(istate);
	struct cache_entry **entries = NULL, *ce;
	int i, nr_entries = 0, nr_alloc = 0;

	si->delete_bitmap = ewah_new();
	si->replace_bitmap = ewah_new();

	if (si->base) {
		/* Go through istate->cache[] and mark CE_MATCHED to
		 * entry with positive index. We'll go through
		 * base->cache[] later to delete all entries in base
		 * that are not marked with either CE_MATCHED or
		 * CE_UPDATE_IN_BASE. If istate->cache[i] is a
		 * duplicate, deduplicate it.
		 */
		for (i = 0; i < istate->cache_nr; i++) {
			struct cache_entry *base;
			/* namelen is checked separately */
			const unsigned int ondisk_flags =
				CE_STAGEMASK | CE_VALID | CE_EXTENDED_FLAGS;
			unsigned int ce_flags, base_flags, ret;
			ce = istate->cache[i];
			if (!ce->index)
				continue;
			if (ce->index > si->base->cache_nr) {
				ce->index = 0;
				continue;
			}
			ce->ce_flags |= CE_MATCHED; /* or "shared" */
			base = si->base->cache[ce->index - 1];
			if (ce == base)
				continue;
			if (ce->ce_namelen != base->ce_namelen ||
			    strcmp(ce->name, base->name)) {
				ce->index = 0;
				continue;
			}
			ce_flags = ce->ce_flags;
			base_flags = base->ce_flags;
			/* only on-disk flags matter */
			ce->ce_flags   &= ondisk_flags;
			base->ce_flags &= ondisk_flags;
			ret = memcmp(&ce->ce_stat_data, &base->ce_stat_data,
				     offsetof(struct cache_entry, name) -
				     offsetof(struct cache_entry, ce_stat_data));
			ce->ce_flags = ce_flags;
			base->ce_flags = base_flags;
			if (ret)
				ce->ce_flags |= CE_UPDATE_IN_BASE;
			free(base);
			si->base->cache[ce->index - 1] = ce;
		}
		for (i = 0; i < si->base->cache_nr; i++) {
			ce = si->base->cache[i];
			if ((ce->ce_flags & CE_REMOVE) ||
			    !(ce->ce_flags & CE_MATCHED))
				ewah_set(si->delete_bitmap, i);
			else if (ce->ce_flags & CE_UPDATE_IN_BASE) {
				ewah_set(si->replace_bitmap, i);
				ce->ce_flags |= CE_STRIP_NAME;
				ALLOC_GROW(entries, nr_entries+1, nr_alloc);
				entries[nr_entries++] = ce;
			}
		}
	}

	for (i = 0; i < istate->cache_nr; i++) {
		ce = istate->cache[i];
		if ((!si->base || !ce->index) && !(ce->ce_flags & CE_REMOVE)) {
			assert(!(ce->ce_flags & CE_STRIP_NAME));
			ALLOC_GROW(entries, nr_entries+1, nr_alloc);
			entries[nr_entries++] = ce;
		}
		ce->ce_flags &= ~CE_MATCHED;
	}

	/*
	 * take cache[] out temporarily, put entries[] in its place
	 * for writing
	 */
	si->saved_cache = istate->cache;
	si->saved_cache_nr = istate->cache_nr;
	istate->cache = entries;
	istate->cache_nr = nr_entries;
}