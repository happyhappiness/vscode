static void alloc_table(struct hashmap *map, unsigned int size)
{
	map->tablesize = size;
	map->table = xcalloc(size, sizeof(struct hashmap_entry *));

	/* calculate resize thresholds for new size */
	map->grow_at = (unsigned int) ((uint64_t) size * HASHMAP_LOAD_FACTOR / 100);
	if (size <= HASHMAP_INITIAL_SIZE)
		map->shrink_at = 0;
	else
		/*
		 * The shrink-threshold must be slightly smaller than
		 * (grow-threshold / resize-factor) to prevent erratic resizing,
		 * thus we divide by (resize-factor + 1).
		 */
		map->shrink_at = map->grow_at / ((1 << HASHMAP_RESIZE_BITS) + 1);
}