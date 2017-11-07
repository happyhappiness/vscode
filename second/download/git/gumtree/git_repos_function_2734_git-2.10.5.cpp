static int locate_in_src_index(const struct cache_entry *ce,
			       struct unpack_trees_options *o)
{
	struct index_state *index = o->src_index;
	int len = ce_namelen(ce);
	int pos = index_name_pos(index, ce->name, len);
	if (pos < 0)
		pos = -1 - pos;
	return pos;
}