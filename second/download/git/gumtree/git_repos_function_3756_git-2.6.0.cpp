static inline unsigned int bucket(const struct hashmap *map,
		const struct hashmap_entry *key)
{
	return key->hash & (map->tablesize - 1);
}