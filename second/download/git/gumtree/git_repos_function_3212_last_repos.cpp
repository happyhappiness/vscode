static void mark_ce_used_same_name(struct cache_entry *ce,
				   struct unpack_trees_options *o)
{
	struct index_state *index = o->src_index;
	int len = ce_namelen(ce);
	int pos;

	for (pos = locate_in_src_index(ce, o); pos < index->cache_nr; pos++) {
		struct cache_entry *next = index->cache[pos];
		if (len != ce_namelen(next) ||
		    memcmp(ce->name, next->name, len))
			break;
		mark_ce_used(next, o);
	}
}