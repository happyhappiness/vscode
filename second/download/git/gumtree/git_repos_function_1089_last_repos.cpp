static char short_submodule_status(struct wt_status_change_data *d) {
	if (d->new_submodule_commits)
		return 'M';
	if (d->dirty_submodule & DIRTY_SUBMODULE_MODIFIED)
		return 'm';
	if (d->dirty_submodule & DIRTY_SUBMODULE_UNTRACKED)
		return '?';
	return d->worktree_status;
}