int update_main_cache_tree(int flags)
{
	if (!the_index.cache_tree)
		the_index.cache_tree = cache_tree();
	return cache_tree_update(&the_index, flags);
}