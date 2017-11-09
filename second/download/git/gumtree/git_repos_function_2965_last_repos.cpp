static struct tree *empty_tree(void)
{
	return lookup_tree(&empty_tree_oid);
}