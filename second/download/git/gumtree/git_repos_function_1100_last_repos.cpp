static int wt_status_check_worktree_changes(struct wt_status *s,
					     int *dirty_submodules)
{
	int i;
	int changes = 0;

	*dirty_submodules = 0;

	for (i = 0; i < s->change.nr; i++) {
		struct wt_status_change_data *d;
		d = s->change.items[i].util;
		if (!d->worktree_status ||
		    d->worktree_status == DIFF_STATUS_UNMERGED)
			continue;
		if (!changes)
			changes = 1;
		if (d->dirty_submodule)
			*dirty_submodules = 1;
		if (d->worktree_status == DIFF_STATUS_DELETED)
			changes = -1;
	}
	return changes;
}