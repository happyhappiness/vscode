void prime_cache_tree(struct index_state *istate, struct tree *tree)
{
	cache_tree_free(&istate->cache_tree);
	istate->cache_tree = cache_tree();
	prime_cache_tree_rec(istate->cache_tree, tree);
	istate->cache_changed |= CACHE_TREE_CHANGED;
}