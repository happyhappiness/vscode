static struct merge_parent *find_merge_parent(struct merge_parents *table,
					      unsigned char *given,
					      unsigned char *commit)
{
	int i;
	for (i = 0; i < table->nr; i++) {
		if (given && hashcmp(table->item[i].given, given))
			continue;
		if (commit && hashcmp(table->item[i].commit, commit))
			continue;
		return &table->item[i];
	}
	return NULL;
}