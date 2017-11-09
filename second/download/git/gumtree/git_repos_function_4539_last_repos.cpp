static void rehash(struct hashmap *map, unsigned int newsize)
{
	unsigned int i, oldsize = map->tablesize;
	struct hashmap_entry **oldtable = map->table;

	if (map->disallow_rehash)
		return;

	alloc_table(map, newsize);
	for (i = 0; i < oldsize; i++) {
		struct hashmap_entry *e = oldtable[i];
		while (e) {
			struct hashmap_entry *next = e->next;
			unsigned int b = bucket(map, e);
			e->next = map->table[b];
			map->table[b] = e;
			e = next;
		}
	}
	free(oldtable);
}