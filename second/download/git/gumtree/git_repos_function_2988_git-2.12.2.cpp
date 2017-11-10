static inline int call_unpack_fn(const struct cache_entry * const *src,
				 struct unpack_trees_options *o)
{
	int ret = o->fn(src, o);
	if (ret > 0)
		ret = 0;
	return ret;
}