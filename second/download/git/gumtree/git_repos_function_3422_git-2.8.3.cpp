void add_name_hash(struct index_state *istate, struct cache_entry *ce)
{
	if (istate->name_hash_initialized)
		hash_index_entry(istate, ce);
}