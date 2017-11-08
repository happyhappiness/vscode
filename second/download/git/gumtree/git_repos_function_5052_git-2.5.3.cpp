static void add_merge_parent(struct merge_parents *table,
			     unsigned char *given,
			     unsigned char *commit)
{
	if (table->nr && find_merge_parent(table, given, commit))
		return;
	ALLOC_GROW(table->item, table->nr + 1, table->alloc);
	hashcpy(table->item[table->nr].given, given);
	hashcpy(table->item[table->nr].commit, commit);
	table->item[table->nr].used = 0;
	table->nr++;
}