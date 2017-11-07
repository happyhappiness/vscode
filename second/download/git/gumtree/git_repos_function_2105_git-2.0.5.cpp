static void add_cache_tree(struct cache_tree *it, struct rev_info *revs)
{
	int i;

	if (it->entry_count >= 0)
		add_one_tree(it->sha1, revs);
	for (i = 0; i < it->subtree_nr; i++)
		add_cache_tree(it->down[i]->cache_tree, revs);
}