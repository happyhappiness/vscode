void set_git_work_tree(const char *new_work_tree)
{
	if (git_work_tree_initialized) {
		new_work_tree = real_path(new_work_tree);
		if (strcmp(new_work_tree, work_tree))
			die("internal error: work tree has already been set\n"
			    "Current worktree: %s\nNew worktree: %s",
			    work_tree, new_work_tree);
		return;
	}
	git_work_tree_initialized = 1;
	work_tree = xstrdup(real_path(new_work_tree));
	if (setenv(GIT_WORK_TREE_ENVIRONMENT, work_tree, 1))
		die("could not set GIT_WORK_TREE to '%s'", work_tree);
}