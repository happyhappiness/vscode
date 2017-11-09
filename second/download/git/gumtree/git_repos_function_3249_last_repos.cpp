static int verify_absent(const struct cache_entry *ce,
			 enum unpack_trees_error_types error_type,
			 struct unpack_trees_options *o)
{
	if (!o->skip_sparse_checkout && (ce->ce_flags & CE_NEW_SKIP_WORKTREE))
		return 0;
	return verify_absent_1(ce, error_type, o);
}