void setup_work_tree(void)
{
	const char *work_tree, *git_dir;
	static int initialized = 0;

	if (initialized)
		return;

	if (work_tree_config_is_bogus)
		die("unable to set up work tree using invalid config");

	work_tree = get_git_work_tree();
	git_dir = get_git_dir();
	if (!is_absolute_path(git_dir))
		git_dir = real_path(get_git_dir());
	if (!work_tree || chdir(work_tree))
		die("This operation must be run in a work tree");

	/*
	 * Make sure subsequent git processes find correct worktree
	 * if $GIT_WORK_TREE is set relative
	 */
	if (getenv(GIT_WORK_TREE_ENVIRONMENT))
		setenv(GIT_WORK_TREE_ENVIRONMENT, ".", 1);

	set_git_dir(remove_leading_path(git_dir, work_tree));
	initialized = 1;
}