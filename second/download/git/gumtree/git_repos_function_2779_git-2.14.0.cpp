static inline void *hashmap_get_from_hash(const struct hashmap *map,
					  unsigned int hash,
					  const void *keydata)
{
	struct hashmap_entry key;
	hashmap_entry_init(&key, hash);
	return hashmap_get(map, &key, keydata);
}