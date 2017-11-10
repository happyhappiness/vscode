static int list_paths(struct string_list *list, const char *with_tree,
		      const char *prefix, const struct pathspec *pattern)
{
	int i, ret;
	char *m;

	if (!pattern->nr)
		return 0;

	m = xcalloc(1, pattern->nr);

	if (with_tree) {
		char *max_prefix = common_prefix(pattern);
		overlay_tree_on_cache(with_tree, max_prefix ? max_prefix : prefix);
		free(max_prefix);
	}

	for (i = 0; i < active_nr; i++) {
		const struct cache_entry *ce = active_cache[i];
		struct string_list_item *item;

		if (ce->ce_flags & CE_UPDATE)
			continue;
		if (!ce_path_match(ce, pattern, m))
			continue;
		item = string_list_insert(list, ce->name);
		if (ce_skip_worktree(ce))
			item->util = item; /* better a valid pointer than a fake one */
	}

	ret = report_path_error(m, pattern, prefix);
	free(m);
	return ret;
}