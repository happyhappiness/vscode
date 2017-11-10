static struct cache_entry *next_cache_entry(struct unpack_trees_options *o)
{
	const struct index_state *index = o->src_index;
	int pos = o->cache_bottom;

	while (pos < index->cache_nr) {
		struct cache_entry *ce = index->cache[pos];
		if (!(ce->ce_flags & CE_UNPACKED))
			return ce;
		pos++;
	}
	return NULL;
}