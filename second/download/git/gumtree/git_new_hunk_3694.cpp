{
	int i;
	int intent_to_add = *(int *)data;

	for (i = 0; i < q->nr; i++) {
		struct diff_filespec *one = q->queue[i]->one;
		int is_missing = !(one->mode && !is_null_oid(&one->oid));
		struct cache_entry *ce;

		if (is_missing && !intent_to_add) {
			remove_file_from_cache(one->path);
			continue;
		}

		ce = make_cache_entry(one->mode, one->oid.hash, one->path,
				      0, 0);
		if (!ce)
			die(_("make_cache_entry failed for path '%s'"),
			    one->path);
		if (is_missing) {
			ce->ce_flags |= CE_INTENT_TO_ADD;
