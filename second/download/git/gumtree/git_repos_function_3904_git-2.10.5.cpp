static inline struct hashmap_entry **find_entry_ptr(const struct hashmap *map,
		const struct hashmap_entry *key, const void *keydata)
{
	struct hashmap_entry **e = &map->table[bucket(map, key)];
	while (*e && !entry_equals(map, *e, key, keydata))
		e = &(*e)->next;
	return e;
}