struct split_index *init_split_index(struct index_state *istate)
{
	if (!istate->split_index) {
		istate->split_index = xcalloc(1, sizeof(*istate->split_index));
		istate->split_index->refcount = 1;
	}
	return istate->split_index;
}