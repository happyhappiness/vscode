void prime_cache_tree(struct cache_tree **it, struct tree *tree)
{
	cache_tree_free(it);
	*it = cache_tree();
	prime_cache_tree_rec(*it, tree);
}