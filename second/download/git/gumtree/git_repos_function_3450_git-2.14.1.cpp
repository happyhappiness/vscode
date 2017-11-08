static struct ref_store_hash_entry *alloc_ref_store_hash_entry(
		const char *name, struct ref_store *refs)
{
	struct ref_store_hash_entry *entry;

	FLEX_ALLOC_STR(entry, name, name);
	hashmap_entry_init(entry, strhash(name));
	entry->refs = refs;
	return entry;
}