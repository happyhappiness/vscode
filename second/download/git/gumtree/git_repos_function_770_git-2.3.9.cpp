static void wt_status_collect_updated_cb(struct diff_queue_struct *q,
					 struct diff_options *options,
					 void *data)
{
	struct wt_status *s = data;
	int i;

	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p;
		struct string_list_item *it;
		struct wt_status_change_data *d;

		p = q->queue[i];
		it = string_list_insert(&s->change, p->two->path);
		d = it->util;
		if (!d) {
			d = xcalloc(1, sizeof(*d));
			it->util = d;
		}
		if (!d->index_status)
			d->index_status = p->status;
		switch (p->status) {
		case DIFF_STATUS_COPIED:
		case DIFF_STATUS_RENAMED:
			d->head_path = xstrdup(p->one->path);
			break;
		case DIFF_STATUS_UNMERGED:
			d->stagemask = unmerged_mask(p->two->path);
			break;
		}
	}
}