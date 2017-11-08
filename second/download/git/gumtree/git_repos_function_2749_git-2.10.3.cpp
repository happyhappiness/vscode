static struct cache_entry *find_cache_entry(struct traverse_info *info,
					    const struct name_entry *p)
{
	int pos = find_cache_pos(info, p);
	struct unpack_trees_options *o = info->data;

	if (0 <= pos)
		return o->src_index->cache[pos];
	else
		return NULL;
}