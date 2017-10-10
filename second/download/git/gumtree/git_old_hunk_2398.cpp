{
	const char *work_tree, *git_dir;
	static int initialized = 0;

	if (initialized)
		return;
	work_tree = get_git_work_tree();
	git_dir = get_git_dir();
	if (!is_absolute_path(git_dir))
		git_dir = real_path(get_git_dir());
	if (!work_tree || chdir(work_tree))
		die("This operation must be run in a work tree");
