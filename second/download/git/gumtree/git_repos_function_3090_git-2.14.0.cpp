int is_worktree_being_rebased(const struct worktree *wt,
			      const char *target)
{
	struct wt_status_state state;
	int found_rebase;

	memset(&state, 0, sizeof(state));
	found_rebase = wt_status_check_rebase(wt, &state) &&
		((state.rebase_in_progress ||
		  state.rebase_interactive_in_progress) &&
		 state.branch &&
		 starts_with(target, "refs/heads/") &&
		 !strcmp(state.branch, target + strlen("refs/heads/")));
	free(state.branch);
	free(state.onto);
	return found_rebase;
}