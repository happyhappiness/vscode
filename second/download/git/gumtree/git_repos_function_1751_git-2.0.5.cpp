int diff_tree_sha1(const unsigned char *old, const unsigned char *new, const char *base, struct diff_options *opt)
{
	void *tree1, *tree2;
	struct tree_desc t1, t2;
	unsigned long size1, size2;
	int retval;

	tree1 = fill_tree_descriptor(&t1, old);
	tree2 = fill_tree_descriptor(&t2, new);
	size1 = t1.size;
	size2 = t2.size;
	retval = diff_tree(&t1, &t2, base, opt);
	if (!*base && DIFF_OPT_TST(opt, FOLLOW_RENAMES) && diff_might_be_rename()) {
		init_tree_desc(&t1, tree1, size1);
		init_tree_desc(&t2, tree2, size2);
		try_to_follow_renames(&t1, &t2, base, opt);
	}
	free(tree1);
	free(tree2);
	return retval;
}