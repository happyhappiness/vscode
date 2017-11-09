int rerere_remaining(struct string_list *merge_rr)
{
	int i;
	if (setup_rerere(merge_rr, RERERE_READONLY))
		return 0;
	if (read_cache() < 0)
		return error("Could not read index");

	for (i = 0; i < active_nr;) {
		int conflict_type;
		const struct cache_entry *e = active_cache[i];
		i = check_one_conflict(i, &conflict_type);
		if (conflict_type == PUNTED)
			string_list_insert(merge_rr, (const char *)e->name);
		else if (conflict_type == RESOLVED) {
			struct string_list_item *it;
			it = string_list_lookup(merge_rr, (const char *)e->name);
			if (it != NULL) {
				free_rerere_id(it);
				it->util = RERERE_RESOLVED;
			}
		}
	}
	return 0;
}