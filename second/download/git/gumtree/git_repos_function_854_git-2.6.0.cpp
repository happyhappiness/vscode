static void wt_status_collect_changes_initial(struct wt_status *s)
{
	int i;

	for (i = 0; i < active_nr; i++) {
		struct string_list_item *it;
		struct wt_status_change_data *d;
		const struct cache_entry *ce = active_cache[i];

		if (!ce_path_match(ce, &s->pathspec, NULL))
			continue;
		it = string_list_insert(&s->change, ce->name);
		d = it->util;
		if (!d) {
			d = xcalloc(1, sizeof(*d));
			it->util = d;
		}
		if (ce_stage(ce)) {
			d->index_status = DIFF_STATUS_UNMERGED;
			d->stagemask |= (1 << (ce_stage(ce) - 1));
		}
		else
			d->index_status = DIFF_STATUS_ADDED;
	}
}