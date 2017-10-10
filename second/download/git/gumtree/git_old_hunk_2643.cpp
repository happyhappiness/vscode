	return 0;
}

int rerere_remaining(struct string_list *merge_rr)
{
	int i;
	if (read_cache() < 0)
		return error("Could not read index");

	for (i = 0; i < active_nr;) {
		int conflict_type;
		const struct cache_entry *e = active_cache[i];
