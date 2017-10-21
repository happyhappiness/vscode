	if (!(tbl = new(struct hashtable))
	 || !(tbl->nodes = new_array0(char, size * node_size)))
		out_of_memory("hashtable_create");
	tbl->size = size;
	tbl->entries = 0;
	tbl->node_size = node_size;
	tbl->key64 = key64;

	return tbl;
}

void hashtable_destroy(struct hashtable *tbl)
{
