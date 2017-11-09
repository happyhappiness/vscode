void hashtable_destroy(struct hashtable *tbl)
{
	if (DEBUG_GTE(HASH, 1)) {
		rprintf(FINFO, "[%s] destroyed hashtable %lx (size: %d, keys: %d-bit)\n",
			who_am_i(), (long)tbl, tbl->size, tbl->key64 ? 64 : 32);
	}
	free(tbl->nodes);
	free(tbl);
}