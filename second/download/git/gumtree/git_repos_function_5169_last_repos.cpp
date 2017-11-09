static int read_tree_some(struct tree *tree, const struct pathspec *pathspec)
{
	read_tree_recursive(tree, "", 0, 0, pathspec, update_some, NULL);

	/* update the index with the given tree's info
	 * for all args, expanding wildcards, and exit
	 * with any non-zero return code.
	 */
	return 0;
}