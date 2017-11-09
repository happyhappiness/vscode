static int has_unmerged(struct wt_status *s)
{
	int i;

	for (i = 0; i < s->change.nr; i++) {
		struct wt_status_change_data *d;
		d = s->change.items[i].util;
		if (d->stagemask)
			return 1;
	}
	return 0;
}