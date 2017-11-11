void merge_base_index(struct index_state *istate)
{
	struct split_index *si = istate->split_index;
	unsigned int i;

	mark_base_index_entries(si->base);

	si->saved_cache	    = istate->cache;
	si->saved_cache_nr  = istate->cache_nr;
	istate->cache_nr    = si->base->cache_nr;
	istate->cache	    = NULL;
	istate->cache_alloc = 0;
	ALLOC_GROW(istate->cache, istate->cache_nr, istate->cache_alloc);
	COPY_ARRAY(istate->cache, si->base->cache, istate->cache_nr);

	si->nr_deletions = 0;
	si->nr_replacements = 0;
	ewah_each_bit(si->replace_bitmap, replace_entry, istate);
	ewah_each_bit(si->delete_bitmap, mark_entry_for_delete, istate);
	if (si->nr_deletions)
		remove_marked_cache_entries(istate);

	for (i = si->nr_replacements; i < si->saved_cache_nr; i++) {
		if (!ce_namelen(si->saved_cache[i]))
			die("corrupt link extension, entry %d should "
			    "have non-zero length name", i);
		add_index_entry(istate, si->saved_cache[i],
				ADD_CACHE_OK_TO_ADD |
				ADD_CACHE_KEEP_CACHE_TREE |
				/*
				 * we may have to replay what
				 * merge-recursive.c:update_stages()
				 * does, which has this flag on
				 */
				ADD_CACHE_SKIP_DFCHECK);
		si->saved_cache[i] = NULL;
	}

	ewah_free(si->delete_bitmap);
	ewah_free(si->replace_bitmap);
	free(si->saved_cache);
	si->delete_bitmap  = NULL;
	si->replace_bitmap = NULL;
	si->saved_cache	   = NULL;
	si->saved_cache_nr = 0;
}