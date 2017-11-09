static void invalidate_ce_path(const struct cache_entry *ce,
			       struct unpack_trees_options *o)
{
	if (!ce)
		return;
	cache_tree_invalidate_path(o->src_index, ce->name);
	untracked_cache_invalidate_path(o->src_index, ce->name);
}