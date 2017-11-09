static struct string_list *get_unmerged(void)
{
	struct string_list *unmerged = xcalloc(1, sizeof(struct string_list));
	int i;

	unmerged->strdup_strings = 1;

	for (i = 0; i < active_nr; i++) {
		struct string_list_item *item;
		struct stage_data *e;
		const struct cache_entry *ce = active_cache[i];
		if (!ce_stage(ce))
			continue;

		item = string_list_lookup(unmerged, ce->name);
		if (!item) {
			item = string_list_insert(unmerged, ce->name);
			item->util = xcalloc(1, sizeof(struct stage_data));
		}
		e = item->util;
		e->stages[ce_stage(ce)].mode = ce->ce_mode;
		oidcpy(&e->stages[ce_stage(ce)].oid, &ce->oid);
	}

	return unmerged;
}