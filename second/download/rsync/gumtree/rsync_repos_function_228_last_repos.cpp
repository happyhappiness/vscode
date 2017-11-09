struct hashtable *hashtable_create(int size, int key64)
{
	int req = size;
	struct hashtable *tbl;
	int node_size = key64 ? sizeof (struct ht_int64_node)
			      : sizeof (struct ht_int32_node);

	/* Pick a power of 2 that can hold the requested size. */
	if (size & (size-1) || size < 16) {
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
	tbl->key64 = key64 ? 1 : 0;

	if (DEBUG_GTE(HASH, 1)) {
		char buf[32];
		if (req != size)
			snprintf(buf, sizeof buf, "req: %d, ", req);
		else
			*buf = '\0';
		rprintf(FINFO, "[%s] created hashtable %lx (%ssize: %d, keys: %d-bit)\n",
			who_am_i(), (long)tbl, buf, size, key64 ? 64 : 32);
	}

	return tbl;
}