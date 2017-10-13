static void wt_status_collect_changed_cb(struct diff_queue_struct *q,
					 struct diff_options *options,
					 void *data)
{
	struct wt_status *s = data;
	int i;

	if (!q->nr)
		return;
	s->workdir_dirty = 1;
	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p;
		struct string_list_item *it;
		struct wt_status_change_data *d;

		p = q->queue[i];
		it = string_list_insert(&s->change, p->one->path);
		d = it->util;
		if (!d) {
			d = xcalloc(1, sizeof(*d));
			it->util = d;
		}
		if (!d->worktree_status)
			d->worktree_status = p->status;
		d->dirty_submodule = p->two->dirty_submodule;
		if (S_ISGITLINK(p->two->mode))
			d->new_submodule_commits = !!oidcmp(&p->one->oid,
							    &p->two->oid);

		switch (p->status) {
		case DIFF_STATUS_ADDED:
			d->mode_worktree = p->two->mode;
			break;

		case DIFF_STATUS_DELETED:
			d->mode_index = p->one->mode;
			oidcpy(&d->oid_index, &p->one->oid);
			/* mode_worktree is zero for a delete. */
			break;

		case DIFF_STATUS_MODIFIED:
		case DIFF_STATUS_TYPE_CHANGED:
		case DIFF_STATUS_UNMERGED:
			d->mode_index = p->one->mode;
			d->mode_worktree = p->two->mode;
			oidcpy(&d->oid_index, &p->one->oid);
			break;

		case DIFF_STATUS_UNKNOWN:
			die("BUG: worktree status unknown???");
			break;
		}

	}
}