static int compare_worktree(const void *a_, const void *b_)
{
	const struct worktree *const *a = a_;
	const struct worktree *const *b = b_;
	return fspathcmp((*a)->path, (*b)->path);
}