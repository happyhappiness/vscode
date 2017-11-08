static int verify_uptodate_sparse(const struct cache_entry *ce,
				  struct unpack_trees_options *o)
{
	return verify_uptodate_1(ce, o, ERROR_SPARSE_NOT_UPTODATE_FILE);
}