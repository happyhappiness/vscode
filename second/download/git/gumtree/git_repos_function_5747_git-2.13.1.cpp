static void add_merge_parent(struct merge_parents *table,
			     struct object_id *given,
			     struct object_id *commit)
{
	if (table->nr && find_merge_parent(table, given, commit))
		return;
	ALLOC_GROW(table->item, table->nr + 1, table->alloc);
	oidcpy(&table->item[table->nr].given, given);
	oidcpy(&table->item[table->nr].commit, commit);
	table->item[table->nr].used = 0;
	table->nr++;
}