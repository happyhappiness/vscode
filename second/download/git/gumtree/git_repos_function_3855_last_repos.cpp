void replace_index_entry_in_base(struct index_state *istate,
				 struct cache_entry *old,
				 struct cache_entry *new)
{
	if (old->index &&
	    istate->split_index &&
	    istate->split_index->base &&
	    old->index <= istate->split_index->base->cache_nr) {
		new->index = old->index;
		if (old != istate->split_index->base->cache[new->index - 1])
			free(istate->split_index->base->cache[new->index - 1]);
		istate->split_index->base->cache[new->index - 1] = new;
	}
}