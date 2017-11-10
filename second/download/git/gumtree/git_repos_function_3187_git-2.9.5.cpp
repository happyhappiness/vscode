static int get_files_dirs(struct merge_options *o, struct tree *tree)
{
	int n;
	struct pathspec match_all;
	memset(&match_all, 0, sizeof(match_all));
	if (read_tree_recursive(tree, "", 0, 0, &match_all, save_files_dirs, o))
		return 0;
	n = o->current_file_set.nr + o->current_directory_set.nr;
	return n;
}