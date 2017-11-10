static int keep_entry(const struct cache_entry *ce,
		      struct unpack_trees_options *o)
{
	add_entry(o, ce, 0, 0);
	return 1;
}