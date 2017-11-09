static void mark_entry_for_delete(size_t pos, void *data)
{
	struct index_state *istate = data;
	if (pos >= istate->cache_nr)
		die("position for delete %d exceeds base index size %d",
		    (int)pos, istate->cache_nr);
	istate->cache[pos]->ce_flags |= CE_REMOVE;
	istate->split_index->nr_deletions = 1;
}