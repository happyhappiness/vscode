static int list_tree(struct object_id *oid)
{
	struct tree *tree;

	if (nr_trees >= MAX_UNPACK_TREES)
		die("I cannot read more than %d trees", MAX_UNPACK_TREES);
	tree = parse_tree_indirect(oid);
	if (!tree)
		return -1;
	trees[nr_trees++] = tree;
	return 0;
}