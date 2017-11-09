static int find_conflict(struct string_list *conflict)
{
	int i;
	if (read_cache() < 0)
		return error("Could not read index");

	for (i = 0; i < active_nr;) {
		int conflict_type;
		const struct cache_entry *e = active_cache[i];
		i = check_one_conflict(i, &conflict_type);
		if (conflict_type == THREE_STAGED)
			string_list_insert(conflict, (const char *)e->name);
	}
	return 0;
}