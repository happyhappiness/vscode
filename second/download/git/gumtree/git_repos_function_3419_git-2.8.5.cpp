static void hash_index_entry(struct index_state *istate, struct cache_entry *ce)
{
	if (ce->ce_flags & CE_HASHED)
		return;
	ce->ce_flags |= CE_HASHED;
	hashmap_entry_init(ce, memihash(ce->name, ce_namelen(ce)));
	hashmap_add(&istate->name_hash, ce);

	if (ignore_case)
		add_dir_entry(istate, ce);
}