static void wt_porcelain_v2_submodule_state(
	struct wt_status_change_data *d,
	char sub[5])
{
	if (S_ISGITLINK(d->mode_head) ||
		S_ISGITLINK(d->mode_index) ||
		S_ISGITLINK(d->mode_worktree)) {
		sub[0] = 'S';
		sub[1] = d->new_submodule_commits ? 'C' : '.';
		sub[2] = (d->dirty_submodule & DIRTY_SUBMODULE_MODIFIED) ? 'M' : '.';
		sub[3] = (d->dirty_submodule & DIRTY_SUBMODULE_UNTRACKED) ? 'U' : '.';
	} else {
		sub[0] = 'N';
		sub[1] = '.';
		sub[2] = '.';
		sub[3] = '.';
	}
	sub[4] = 0;
}