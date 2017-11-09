static void lazy_init_name_hash(struct index_state *istate)
{
	if (istate->name_hash_initialized)
		return;
	hashmap_init(&istate->name_hash, (hashmap_cmp_fn) cache_entry_cmp,
			NULL, istate->cache_nr);
	hashmap_init(&istate->dir_hash, (hashmap_cmp_fn) dir_entry_cmp,
			NULL, istate->cache_nr);

	if (lookup_lazy_params(istate)) {
		hashmap_disallow_rehash(&istate->dir_hash, 1);
		threaded_lazy_init_name_hash(istate);
		hashmap_disallow_rehash(&istate->dir_hash, 0);
	} else {
		int nr;
		for (nr = 0; nr < istate->cache_nr; nr++)
			hash_index_entry(istate, istate->cache[nr]);
	}

	istate->name_hash_initialized = 1;
}