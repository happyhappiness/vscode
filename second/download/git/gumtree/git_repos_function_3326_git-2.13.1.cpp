static struct ref_store *lookup_submodule_ref_store(const char *submodule)
{
	struct submodule_hash_entry *entry;

	if (!submodule_ref_stores.tablesize)
		/* It's initialized on demand in register_ref_store(). */
		return NULL;

	entry = hashmap_get_from_hash(&submodule_ref_stores,
				      strhash(submodule), submodule);
	return entry ? entry->refs : NULL;
}