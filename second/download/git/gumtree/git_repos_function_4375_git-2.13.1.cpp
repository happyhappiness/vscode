static inline int entry_equals(const struct hashmap *map,
		const struct hashmap_entry *e1, const struct hashmap_entry *e2,
		const void *keydata)
{
	return (e1 == e2) || (e1->hash == e2->hash && !map->cmpfn(e1, e2, keydata));
}