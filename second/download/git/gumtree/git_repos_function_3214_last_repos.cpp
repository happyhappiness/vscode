static void add_same_unmerged(const struct cache_entry *ce,
			      struct unpack_trees_options *o)
{
	struct index_state *index = o->src_index;
	int len = ce_namelen(ce);
	int pos = index_name_pos(index, ce->name, len);

	if (0 <= pos)
		die("programming error in a caller of mark_ce_used_same_name");
	for (pos = -pos - 1; pos < index->cache_nr; pos++) {
		struct cache_entry *next = index->cache[pos];
		if (len != ce_namelen(next) ||
		    memcmp(ce->name, next->name, len))
			break;
		add_entry(o, next, 0, 0);
		mark_ce_used(next, o);
	}
}