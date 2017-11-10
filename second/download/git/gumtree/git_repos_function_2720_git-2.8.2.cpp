int oneway_merge(const struct cache_entry * const *src,
		 struct unpack_trees_options *o)
{
	const struct cache_entry *old = src[0];
	const struct cache_entry *a = src[1];

	if (o->merge_size != 1)
		return error("Cannot do a oneway merge of %d trees",
			     o->merge_size);

	if (!a || a == o->df_conflict_entry)
		return deleted_entry(old, old, o);

	if (old && same(old, a)) {
		int update = 0;
		if (o->reset && o->update && !ce_uptodate(old) && !ce_skip_worktree(old)) {
			struct stat st;
			if (lstat(old->name, &st) ||
			    ie_match_stat(o->src_index, old, &st, CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE))
				update |= CE_UPDATE;
		}
		add_entry(o, old, update, 0);
		return 0;
	}
	return merged_entry(a, old, o);
}