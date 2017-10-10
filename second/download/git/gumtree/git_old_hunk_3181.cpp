	if (read_cache() < 0)
		die(_("index file corrupt"));

	for (i = 0; i < active_nr; i++) {
		const struct cache_entry *ce = active_cache[i];

		if (!S_ISGITLINK(ce->ce_mode) ||
		    !match_pathspec(pathspec, ce->name, ce_namelen(ce),
				    0, ps_matched, 1))
			continue;

		ALLOC_GROW(list->entries, list->nr + 1, list->alloc);
		list->entries[list->nr++] = ce;
		while (i + 1 < active_nr &&
		       !strcmp(ce->name, active_cache[i + 1]->name))
