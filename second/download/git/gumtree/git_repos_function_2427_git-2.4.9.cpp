static int verify_absent_sparse(const struct cache_entry *ce,
				enum unpack_trees_error_types error_type,
				struct unpack_trees_options *o)
{
	enum unpack_trees_error_types orphaned_error = error_type;
	if (orphaned_error == ERROR_WOULD_LOSE_UNTRACKED_OVERWRITTEN)
		orphaned_error = ERROR_WOULD_LOSE_ORPHANED_OVERWRITTEN;

	return verify_absent_1(ce, orphaned_error, o);
}