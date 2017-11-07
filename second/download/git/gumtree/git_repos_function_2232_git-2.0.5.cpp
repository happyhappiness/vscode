static int reject_merge(const struct cache_entry *ce,
			struct unpack_trees_options *o)
{
	return add_rejected_path(o, ERROR_WOULD_OVERWRITE, ce->name);
}