void hashtable_destroy(struct hashtable *tbl)
{
	free(tbl->nodes);
	free(tbl);
}