static int unpack_index_entry(struct cache_entry *ce,
			      struct unpack_trees_options *o)
{
	const struct cache_entry *src[MAX_UNPACK_TREES + 1] = { NULL, };
	int ret;

	src[0] = ce;

	mark_ce_used(ce, o);
	if (ce_stage(ce)) {
		if (o->skip_unmerged) {
			add_entry(o, ce, 0, 0);
			return 0;
		}
	}
	ret = call_unpack_fn(src, o);
	if (ce_stage(ce))
		mark_ce_used_same_name(ce, o);
	return ret;
}