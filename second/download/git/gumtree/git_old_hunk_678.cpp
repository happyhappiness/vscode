
	status = run_command(&child);
	if (status)
		exit(status);
}

static int grep_cache(struct grep_opt *opt, const struct pathspec *pathspec, int cached)
{
	int hit = 0;
	int nr;
	read_cache();

	for (nr = 0; nr < active_nr; nr++) {
		const struct cache_entry *ce = active_cache[nr];
		if (!S_ISREG(ce->ce_mode))
			continue;
		if (!ce_path_match(ce, pathspec, NULL))
			continue;
		/*
		 * If CE_VALID is on, we assume worktree file and its cache entry
		 * are identical, even if worktree file has been modified, so use
		 * cache version instead
		 */
		if (cached || (ce->ce_flags & CE_VALID) || ce_skip_worktree(ce)) {
			if (ce_stage(ce) || ce_intent_to_add(ce))
				continue;
			hit |= grep_sha1(opt, ce->oid.hash, ce->name, 0,
					 ce->name);
		}
		else
			hit |= grep_file(opt, ce->name);
		if (ce_stage(ce)) {
			do {
				nr++;
			} while (nr < active_nr &&
				 !strcmp(ce->name, active_cache[nr]->name));
			nr--; /* compensate for loop control */
		}
		if (hit && opt->status_only)
			break;
	}
	return hit;
}

static int grep_tree(struct grep_opt *opt, const struct pathspec *pathspec,
		     struct tree_desc *tree, struct strbuf *base, int tn_len,
		     int check_attr)
{
	int hit = 0;
	enum interesting match = entry_not_interesting;
	struct name_entry entry;
	int old_baselen = base->len;

	while (tree_entry(tree, &entry)) {
		int te_len = tree_entry_len(&entry);

		if (match != all_entries_interesting) {
			match = tree_entry_interesting(&entry, base, tn_len, pathspec);
			if (match == all_entries_not_interesting)
				break;
			if (match == entry_not_interesting)
				continue;
		}

		strbuf_add(base, entry.path, te_len);

		if (S_ISREG(entry.mode)) {
			hit |= grep_sha1(opt, entry.oid->hash, base->buf, tn_len,
					 check_attr ? base->buf + tn_len : NULL);
		}
		else if (S_ISDIR(entry.mode)) {
			enum object_type type;
			struct tree_desc sub;
			void *data;
			unsigned long size;

			data = lock_and_read_sha1_file(entry.oid->hash, &type, &size);
