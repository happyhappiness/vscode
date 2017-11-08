static void merge_trees(struct tree_desc t[3], const char *base)
{
	merge_trees_recursive(t, base, 0);
}