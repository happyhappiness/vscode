int discard_index(struct index_state *istate)
{
	int i;

	for (i = 0; i < istate->cache_nr; i++) {
		if (istate->cache[i]->index &&
		    istate->split_index &&
		    istate->split_index->base &&
		    istate->cache[i]->index <= istate->split_index->base->cache_nr &&
		    istate->cache[i] == istate->split_index->base->cache[istate->cache[i]->index - 1])
			continue;
		free(istate->cache[i]);
	}
	resolve_undo_clear_index(istate);
	istate->cache_nr = 0;
	istate->cache_changed = 0;
	istate->timestamp.sec = 0;
	istate->timestamp.nsec = 0;
	free_name_hash(istate);
	cache_tree_free(&(istate->cache_tree));
	istate->initialized = 0;
	FREE_AND_NULL(istate->cache);
	istate->cache_alloc = 0;
	discard_split_index(istate);
	free_untracked_cache(istate->untracked);
	istate->untracked = NULL;
	return 0;
}