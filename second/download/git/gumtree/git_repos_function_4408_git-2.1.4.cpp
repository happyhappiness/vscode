static void merge_trees_recursive(struct tree_desc t[3], const char *base, int df_conflict)
{
	struct traverse_info info;

	setup_traverse_info(&info, base);
	info.data = &df_conflict;
	info.fn = threeway_callback;
	traverse_trees(3, t, &info);
}