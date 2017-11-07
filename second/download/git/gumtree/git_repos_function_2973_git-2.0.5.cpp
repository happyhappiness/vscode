struct cache_entry *index_file_exists(struct index_state *istate, const char *name, int namelen, int icase)
{
	struct cache_entry *ce;
	struct hashmap_entry key;

	lazy_init_name_hash(istate);

	hashmap_entry_init(&key, memihash(name, namelen));
	ce = hashmap_get(&istate->name_hash, &key, NULL);
	while (ce) {
		if (same_name(ce, name, namelen, icase))
			return ce;
		ce = hashmap_get_next(&istate->name_hash, ce);
	}
	return NULL;
}