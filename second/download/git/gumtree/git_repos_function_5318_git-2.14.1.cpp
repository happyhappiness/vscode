static int needs_work_tree_config(const char *git_dir, const char *work_tree)
{
	if (!strcmp(work_tree, "/") && !strcmp(git_dir, "/.git"))
		return 0;
	if (skip_prefix(git_dir, work_tree, &git_dir) &&
	    !strcmp(git_dir, "/.git"))
		return 0;
	return 1;
}