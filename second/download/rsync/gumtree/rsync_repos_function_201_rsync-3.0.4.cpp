struct hashtable *hashtable_create(int size, int key64)
{
	struct hashtable *tbl;
	int node_size = key64 ? sizeof (struct ht_int64_node)
			      : sizeof (struct ht_int32_node);

	/* Pick a power of 2 that can hold the requested size. */
	if (size & (size-1) || size < 16) {
		int req = size;
		size = 16;
		while (size < req)
			size *= 2;
	}

	if (!(tbl = new(struct hashtable))
	 || !(tbl->nodes = new_array0(char, size * node_size)))
		out_of_memory("hashtable_create");
	tbl->size = size;
	tbl->entries = 0;
	tbl->node_size = node_size;
	tbl->key64 = key64;

	return tbl;
}