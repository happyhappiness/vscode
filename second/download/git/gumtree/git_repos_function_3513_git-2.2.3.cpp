void hashmap_add(struct hashmap *map, void *entry)
{
	unsigned int b = bucket(map, entry);

	/* add entry */
	((struct hashmap_entry *) entry)->next = map->table[b];
	map->table[b] = entry;

	/* fix size and rehash if appropriate */
	map->size++;
	if (map->size > map->grow_at)
		rehash(map, map->tablesize << HASHMAP_RESIZE_BITS);
}