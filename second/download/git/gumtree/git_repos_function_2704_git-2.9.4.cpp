static void restore_cache_bottom(struct traverse_info *info, int bottom)
{
	struct unpack_trees_options *o = info->data;

	if (o->diff_index_cached)
		return;
	o->cache_bottom = bottom;
}