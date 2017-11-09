static void add_entry(struct unpack_trees_options *o,
		      const struct cache_entry *ce,
		      unsigned int set, unsigned int clear)
{
	do_add_entry(o, dup_entry(ce), set, clear);
}