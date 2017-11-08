int wt_status_check_rebase(const struct worktree *wt,
			   struct wt_status_state *state)
{
	struct stat st;

	if (!stat(worktree_git_path(wt, "rebase-apply"), &st)) {
		if (!stat(worktree_git_path(wt, "rebase-apply/applying"), &st)) {
			state->am_in_progress = 1;
			if (!stat(worktree_git_path(wt, "rebase-apply/patch"), &st) && !st.st_size)
				state->am_empty_patch = 1;
		} else {
			state->rebase_in_progress = 1;
			state->branch = get_branch(wt, "rebase-apply/head-name");
			state->onto = get_branch(wt, "rebase-apply/onto");
		}
	} else if (!stat(worktree_git_path(wt, "rebase-merge"), &st)) {
		if (!stat(worktree_git_path(wt, "rebase-merge/interactive"), &st))
			state->rebase_interactive_in_progress = 1;
		else
			state->rebase_in_progress = 1;
		state->branch = get_branch(wt, "rebase-merge/head-name");
		state->onto = get_branch(wt, "rebase-merge/onto");
	} else
		return 0;
	return 1;
}