static void *attr_hashmap_get(struct attr_hashmap *map,
			      const char *key, size_t keylen)
{
	struct attr_hash_entry k;
	struct attr_hash_entry *e;

	if (!map->map.tablesize)
		attr_hashmap_init(map);

	hashmap_entry_init(&k, memhash(key, keylen));
	k.key = key;
	k.keylen = keylen;
	e = hashmap_get(&map->map, &k, NULL);

	return e ? e->value : NULL;
}