static int submodule_hash_cmp(const void *entry, const void *entry_or_key,
			      const void *keydata)
{
	const struct submodule_hash_entry *e1 = entry, *e2 = entry_or_key;
	const char *submodule = keydata ? keydata : e2->submodule;

	return strcmp(e1->submodule, submodule);
}