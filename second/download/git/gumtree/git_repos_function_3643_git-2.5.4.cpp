void hashmap_init(struct hashmap *map, hashmap_cmp_fn equals_function,
		size_t initial_size)
{
	unsigned int size = HASHMAP_INITIAL_SIZE;
	map->size = 0;
	map->cmpfn = equals_function ? equals_function : always_equal;

	/* calculate initial table size and allocate the table */
	initial_size = (unsigned int) ((uint64_t) initial_size * 100
			/ HASHMAP_LOAD_FACTOR);
	while (initial_size > size)
		size <<= HASHMAP_RESIZE_BITS;
	alloc_table(map, size);
}