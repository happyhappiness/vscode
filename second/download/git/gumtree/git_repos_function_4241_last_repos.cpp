static int path_exists(struct tree *tree, const char *path)
{
	const char *paths[] = { path, NULL };
	struct pathspec pathspec;
	int ret;

	parse_pathspec(&pathspec, 0, 0, "", paths);
	pathspec.recursive = 1;
	ret = read_tree_recursive(tree, "", 0, 0, &pathspec,
				  reject_entry, &pathspec);
	clear_pathspec(&pathspec);
	return ret != 0;
}