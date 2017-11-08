static int switch_cache_bottom(struct traverse_info *info)
{
	struct unpack_trees_options *o = info->data;
	int ret, pos;

	if (o->diff_index_cached)
		return 0;
	ret = o->cache_bottom;
	pos = find_cache_pos(info->prev, &info->name);

	if (pos < -1)
		o->cache_bottom = -2 - pos;
	else if (pos < 0)
		o->cache_bottom = o->src_index->cache_nr;
	return ret;
}