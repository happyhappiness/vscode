void add_split_index(struct index_state *istate)
{
	if (!istate->split_index) {
		init_split_index(istate);
		istate->cache_changed |= SPLIT_INDEX_ORDERED;
	}
}