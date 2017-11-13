static void register_submodule_ref_store(struct ref_store *refs,
					 const char *submodule)
{
	if (!submodule_ref_stores.tablesize)
		hashmap_init(&submodule_ref_stores, submodule_hash_cmp, 0);

	if (hashmap_put(&submodule_ref_stores,
			alloc_submodule_hash_entry(submodule, refs)))
		die("BUG: ref_store for submodule '%s' initialized twice",
		    submodule);
}