const char *get_git_work_tree(void)
{
	return the_repository->worktree;
}