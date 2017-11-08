struct cache_entry *index_file_exists(struct index_state *istate, const char *name, int namelen, int icase)
{
	struct cache_entry *ce;

	lazy_init_name_hash(istate);

	ce = hashmap_get_from_hash(&istate->name_hash,
				   memihash(name, namelen), NULL);
	while (ce) {
		if (same_name(ce, name, namelen, icase))
			return ce;
		ce = hashmap_get_next(&istate->name_hash, ce);
	}
	return NULL;
}