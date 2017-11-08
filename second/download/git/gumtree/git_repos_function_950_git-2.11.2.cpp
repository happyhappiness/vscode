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
		case DIFF_STATUS_ADDED:
			/* Leave {mode,oid}_head zero for an add. */
			d->mode_index = p->two->mode;
			oidcpy(&d->oid_index, &p->two->oid);
			break;
		case DIFF_STATUS_DELETED:
			d->mode_head = p->one->mode;
			oidcpy(&d->oid_head, &p->one->oid);
			/* Leave {mode,oid}_index zero for a delete. */
			break;

		case DIFF_STATUS_COPIED:
		case DIFF_STATUS_RENAMED:
			d->head_path = xstrdup(p->one->path);
			d->score = p->score * 100 / MAX_SCORE;
			/* fallthru */
		case DIFF_STATUS_MODIFIED:
		case DIFF_STATUS_TYPE_CHANGED:
			d->mode_head = p->one->mode;
			d->mode_index = p->two->mode;
			oidcpy(&d->oid_head, &p->one->oid);
			oidcpy(&d->oid_index, &p->two->oid);
			break;
		case DIFF_STATUS_UNMERGED:
			d->stagemask = unmerged_mask(p->two->path);
			/*
			 * Don't bother setting {mode,oid}_{head,index} since the print
			 * code will output the stage values directly and not use the
			 * values in these fields.
			 */
			break;
		}
	}
}