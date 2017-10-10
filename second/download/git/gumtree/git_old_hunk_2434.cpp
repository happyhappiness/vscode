	remove_scheduled_dirs();

	for (i = 0; i < index->cache_nr; i++) {
		struct cache_entry *ce = index->cache[i];

		if (ce->ce_flags & CE_UPDATE) {
			display_progress(progress, ++cnt);
			ce->ce_flags &= ~CE_UPDATE;
			if (o->update && !o->dry_run) {
				errs |= checkout_entry(ce, &state, NULL);
			}
		}
