int remote_is_configured(const char *name)
{
	struct remotes_hash_key lookup;
	struct hashmap_entry lookup_entry;
	read_config();

	init_remotes_hash();
	lookup.str = name;
	lookup.len = strlen(name);
	hashmap_entry_init(&lookup_entry, memhash(name, lookup.len));

	return hashmap_get(&remotes_hash, &lookup_entry, &lookup) != NULL;
}