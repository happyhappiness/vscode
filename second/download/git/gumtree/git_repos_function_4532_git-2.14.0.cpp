void *hashmap_iter_next(struct hashmap_iter *iter)
{
	struct hashmap_entry *current = iter->next;
	for (;;) {
		if (current) {
			iter->next = current->next;
			return current;
		}

		if (iter->tablepos >= iter->map->tablesize)
			return NULL;

		current = iter->map->table[iter->tablepos++];
	}
}