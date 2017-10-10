	 * index_file_exists, find all entries with matching hash code and
	 * decide whether the entry matches in same_name.
	 */
	return remove ? !(ce1 == ce2) : 0;
}

static void lazy_init_name_hash(struct index_state *istate)
{
	int nr;

	if (istate->name_hash_initialized)
		return;
	hashmap_init(&istate->name_hash, (hashmap_cmp_fn) cache_entry_cmp,
			istate->cache_nr);
	hashmap_init(&istate->dir_hash, (hashmap_cmp_fn) dir_entry_cmp, 0);
	for (nr = 0; nr < istate->cache_nr; nr++)
		hash_index_entry(istate, istate->cache[nr]);
	istate->name_hash_initialized = 1;
}

void add_name_hash(struct index_state *istate, struct cache_entry *ce)
{
	if (istate->name_hash_initialized)
		hash_index_entry(istate, ce);
}

