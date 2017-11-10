static struct merge_parent *find_merge_parent(struct merge_parents *table,
					      struct object_id *given,
					      struct object_id *commit)
{
	int i;
	for (i = 0; i < table->nr; i++) {
		if (given && oidcmp(&table->item[i].given, given))
			continue;
		if (commit && oidcmp(&table->item[i].commit, commit))
			continue;
		return &table->item[i];
	}
	return NULL;
}