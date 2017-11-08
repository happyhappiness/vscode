static struct ref_store *lookup_ref_store_map(struct hashmap *map,
					      const char *name)
{
	struct ref_store_hash_entry *entry;

	if (!map->tablesize)
		/* It's initialized on demand in register_ref_store(). */
		return NULL;

	entry = hashmap_get_from_hash(map, strhash(name), name);
	return entry ? entry->refs : NULL;
}