static int do_add_entry(struct unpack_trees_options *o, struct cache_entry *ce,
			 unsigned int set, unsigned int clear)
{
	clear |= CE_HASHED;

	if (set & CE_REMOVE)
		set |= CE_WT_REMOVE;

	ce->ce_flags = (ce->ce_flags & ~clear) | set;
	return add_index_entry(&o->result, ce,
			       ADD_CACHE_OK_TO_ADD | ADD_CACHE_OK_TO_REPLACE);
}