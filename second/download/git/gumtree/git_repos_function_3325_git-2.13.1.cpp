static struct submodule_hash_entry *alloc_submodule_hash_entry(
		const char *submodule, struct ref_store *refs)
{
	struct submodule_hash_entry *entry;

	FLEX_ALLOC_STR(entry, submodule, submodule);
	hashmap_entry_init(entry, strhash(submodule));
	entry->refs = refs;
	return entry;
}