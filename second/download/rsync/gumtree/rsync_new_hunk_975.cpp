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

void hashtable_destroy(struct hashtable *tbl)
{
	if (DEBUG_GTE(HASH, 1)) {
		rprintf(FINFO, "[%s] destroyed hashtable %lx (size: %d, keys: %d-bit)\n",
			who_am_i(), (long)tbl, tbl->size, tbl->key64 ? 64 : 32);
	}
	free(tbl->nodes);
	free(tbl);
}

/* This returns the node for the indicated key, either newly created or
 * already existing.  Returns NULL if not allocating and not found. */
