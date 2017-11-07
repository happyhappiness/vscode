static int path_exists(struct tree *tree, const char *path)
{
	const char *paths[] = { path, NULL };
	struct pathspec pathspec;
	int ret;

	parse_pathspec(&pathspec, 0, 0, "", paths);
	ret = read_tree_recursive(tree, "", 0, 0, &pathspec, reject_entry, NULL);
	free_pathspec(&pathspec);
	return ret != 0;
}