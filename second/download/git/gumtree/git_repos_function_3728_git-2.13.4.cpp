void remove_split_index(struct index_state *istate)
{
	if (istate->split_index) {
		/*
		 * can't discard_split_index(&the_index); because that
		 * will destroy split_index->base->cache[], which may
		 * be shared with the_index.cache[]. So yeah we're
		 * leaking a bit here.
		 */
		istate->split_index = NULL;
		istate->cache_changed |= SOMETHING_CHANGED;
	}
}