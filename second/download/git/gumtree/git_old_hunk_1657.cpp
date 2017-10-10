	remove_marked_cache_entries(index);
	remove_scheduled_dirs();

	if (should_update_submodules() && o->update && !o->dry_run)
		reload_gitmodules_file(index, &state);

	for (i = 0; i < index->cache_nr; i++) {
		struct cache_entry *ce = index->cache[i];

		if (ce->ce_flags & CE_UPDATE) {
			if (ce->ce_flags & CE_WT_REMOVE)
				die("BUG: both update and delete flags are set on %s",
