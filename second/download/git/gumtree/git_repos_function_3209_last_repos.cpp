static void mark_ce_used(struct cache_entry *ce, struct unpack_trees_options *o)
{
	ce->ce_flags |= CE_UNPACKED;

	if (o->cache_bottom < o->src_index->cache_nr &&
	    o->src_index->cache[o->cache_bottom] == ce) {
		int bottom = o->cache_bottom;
		while (bottom < o->src_index->cache_nr &&
		       o->src_index->cache[bottom]->ce_flags & CE_UNPACKED)
			bottom++;
		o->cache_bottom = bottom;
	}
}