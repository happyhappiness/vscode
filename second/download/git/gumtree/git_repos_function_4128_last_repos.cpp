void remove_name_hash(struct index_state *istate, struct cache_entry *ce)
{
	if (!istate->name_hash_initialized || !(ce->ce_flags & CE_HASHED))
		return;
	ce->ce_flags &= ~CE_HASHED;
	hashmap_remove(&istate->name_hash, ce, ce);

	if (ignore_case)
		remove_dir_entry(istate, ce);
}