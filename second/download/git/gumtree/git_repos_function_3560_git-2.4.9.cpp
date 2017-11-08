void hashmap_free(struct hashmap *map, int free_entries)
{
	if (!map || !map->table)
		return;
	if (free_entries) {
		struct hashmap_iter iter;
		struct hashmap_entry *e;
		hashmap_iter_init(map, &iter);
		while ((e = hashmap_iter_next(&iter)))
			free(e);
	}
	free(map->table);
	memset(map, 0, sizeof(*map));
}