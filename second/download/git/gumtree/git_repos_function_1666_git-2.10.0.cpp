static inline int parse_tree(struct tree *tree)
{
	return parse_tree_gently(tree, 0);
}