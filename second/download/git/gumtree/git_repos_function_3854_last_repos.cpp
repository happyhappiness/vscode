void save_or_free_index_entry(struct index_state *istate, struct cache_entry *ce)
{
	if (ce->index &&
	    istate->split_index &&
	    istate->split_index->base &&
	    ce->index <= istate->split_index->base->cache_nr &&
	    ce == istate->split_index->base->cache[ce->index - 1])
		ce->ce_flags |= CE_REMOVE;
	else
		free(ce);
}