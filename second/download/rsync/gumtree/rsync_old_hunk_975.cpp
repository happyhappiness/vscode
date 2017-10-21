		out_of_memory("hashtable_create");
	tbl->size = size;
	tbl->entries = 0;
	tbl->node_size = node_size;
	tbl->key64 = key64 ? 1 : 0;

	return tbl;
}

void hashtable_destroy(struct hashtable *tbl)
{
	free(tbl->nodes);
	free(tbl);
}

/* This returns the node for the indicated key, either newly created or
 * already existing.  Returns NULL if not allocating and not found. */
