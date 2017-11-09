static int verify_uptodate_1(const struct cache_entry *ce,
			     struct unpack_trees_options *o,
			     enum unpack_trees_error_types error_type)
{
	struct stat st;

	if (o->index_only)
		return 0;

	/*
	 * CE_VALID and CE_SKIP_WORKTREE cheat, we better check again
	 * if this entry is truly up-to-date because this file may be
	 * overwritten.
	 */
	if ((ce->ce_flags & CE_VALID) || ce_skip_worktree(ce))
		; /* keep checking */
	else if (o->reset || ce_uptodate(ce))
		return 0;

	if (!lstat(ce->name, &st)) {
		int flags = CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE;
		unsigned changed = ie_match_stat(o->src_index, ce, &st, flags);

		if (submodule_from_ce(ce)) {
			int r = check_submodule_move_head(ce,
				"HEAD", oid_to_hex(&ce->oid), o);
			if (r)
				return o->gently ? -1 :
					add_rejected_path(o, error_type, ce->name);
			return 0;
		}

		if (!changed)
			return 0;
		/*
		 * Historic default policy was to allow submodule to be out
		 * of sync wrt the superproject index. If the submodule was
		 * not considered interesting above, we don't care here.
		 */
		if (S_ISGITLINK(ce->ce_mode))
			return 0;

		errno = 0;
	}
	if (errno == ENOENT)
		return 0;
	return o->gently ? -1 :
		add_rejected_path(o, error_type, ce->name);
}