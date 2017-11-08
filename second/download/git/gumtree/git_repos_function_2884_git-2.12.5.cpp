int is_worktree_being_bisected(const struct worktree *wt,
			       const char *target)
{
	struct wt_status_state state;
	int found_rebase;

	memset(&state, 0, sizeof(state));
	found_rebase = wt_status_check_bisect(wt, &state) &&
		state.branch &&
		starts_with(target, "refs/heads/") &&
		!strcmp(state.branch, target + strlen("refs/heads/"));
	free(state.branch);
	return found_rebase;
}