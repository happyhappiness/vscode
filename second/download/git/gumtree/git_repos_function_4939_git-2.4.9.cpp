static int list_tree(unsigned char *sha1)
{
	struct tree *tree;

	if (nr_trees >= MAX_UNPACK_TREES)
		die("I cannot read more than %d trees", MAX_UNPACK_TREES);
	tree = parse_tree_indirect(sha1);
	if (!tree)
		return -1;
	trees[nr_trees++] = tree;
	return 0;
}