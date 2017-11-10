static int verify_uptodate(const struct cache_entry *ce,
			   struct unpack_trees_options *o)
{
	if (!o->skip_sparse_checkout && (ce->ce_flags & CE_NEW_SKIP_WORKTREE))
		return 0;
	return verify_uptodate_1(ce, o, ERROR_NOT_UPTODATE_FILE);
}