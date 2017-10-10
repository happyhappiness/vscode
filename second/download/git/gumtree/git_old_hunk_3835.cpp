	else if (!wt->id)
		return get_git_common_dir();
	else
		return git_common_path("worktrees/%s", wt->id);
}

int is_worktree_being_rebased(const struct worktree *wt,
			      const char *target)
{
	struct wt_status_state state;
	int found_rebase;

