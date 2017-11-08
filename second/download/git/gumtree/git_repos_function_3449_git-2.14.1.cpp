static int ref_store_hash_cmp(const void *unused_cmp_data,
			      const void *entry, const void *entry_or_key,
			      const void *keydata)
{
	const struct ref_store_hash_entry *e1 = entry, *e2 = entry_or_key;
	const char *name = keydata ? keydata : e2->name;

	return strcmp(e1->name, name);
}