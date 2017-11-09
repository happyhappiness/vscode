int add_index_entry(struct index_state *istate, struct cache_entry *ce, int option)
{
	int pos;

	if (option & ADD_CACHE_JUST_APPEND)
		pos = istate->cache_nr;
	else {
		int ret;
		ret = add_index_entry_with_check(istate, ce, option);
		if (ret <= 0)
			return ret;
		pos = ret - 1;
	}

	/* Make sure the array is big enough .. */
	ALLOC_GROW(istate->cache, istate->cache_nr + 1, istate->cache_alloc);

	/* Add it in.. */
	istate->cache_nr++;
	if (istate->cache_nr > pos + 1)
		memmove(istate->cache + pos + 1,
			istate->cache + pos,
			(istate->cache_nr - pos - 1) * sizeof(ce));
	set_index_entry(istate, pos, ce);
	istate->cache_changed |= CE_ENTRY_ADDED;
	return 0;
}