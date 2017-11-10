int wt_status_check_bisect(const struct worktree *wt,
			   struct wt_status_state *state)
{
	struct stat st;

	if (!stat(worktree_git_path(wt, "BISECT_LOG"), &st)) {
		state->bisect_in_progress = 1;
		state->branch = get_branch(wt, "BISECT_START");
		return 1;
	}
	return 0;
}