static int deleted_entry(const struct cache_entry *ce,
			 const struct cache_entry *old,
			 struct unpack_trees_options *o)
{
	/* Did it exist in the index? */
	if (!old) {
		if (verify_absent(ce, ERROR_WOULD_LOSE_UNTRACKED_REMOVED, o))
			return -1;
		return 0;
	}
	if (!(old->ce_flags & CE_CONFLICTED) && verify_uptodate(old, o))
		return -1;
	add_entry(o, ce, CE_REMOVE, 0);
	invalidate_ce_path(ce, o);
	return 1;
}