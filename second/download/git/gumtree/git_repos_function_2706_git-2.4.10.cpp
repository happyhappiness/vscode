struct cache_tree *cache_tree(void)
{
	struct cache_tree *it = xcalloc(1, sizeof(struct cache_tree));
	it->entry_count = -1;
	return it;
}