int is_main_worktree(const struct worktree *wt)
{
	return !wt->id;
}