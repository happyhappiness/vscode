void *hashmap_remove(struct hashmap *map, const void *key, const void *keydata)
{
	struct hashmap_entry *old;
	struct hashmap_entry **e = find_entry_ptr(map, key, keydata);
	if (!*e)
		return NULL;

	/* remove existing entry */
	old = *e;
	*e = old->next;
	old->next = NULL;

	/* fix size and rehash if appropriate */
	map->size--;
	if (map->size < map->shrink_at)
		rehash(map, map->tablesize >> HASHMAP_RESIZE_BITS);
	return old;
}