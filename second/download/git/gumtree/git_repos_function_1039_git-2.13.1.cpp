static void wt_porcelain_v2_print(struct wt_status *s)
{
	struct wt_status_change_data *d;
	struct string_list_item *it;
	int i;

	if (s->show_branch)
		wt_porcelain_v2_print_tracking(s);

	for (i = 0; i < s->change.nr; i++) {
		it = &(s->change.items[i]);
		d = it->util;
		if (!d->stagemask)
			wt_porcelain_v2_print_changed_entry(it, s);
	}

	for (i = 0; i < s->change.nr; i++) {
		it = &(s->change.items[i]);
		d = it->util;
		if (d->stagemask)
			wt_porcelain_v2_print_unmerged_entry(it, s);
	}

	for (i = 0; i < s->untracked.nr; i++) {
		it = &(s->untracked.items[i]);
		wt_porcelain_v2_print_other(it, s, '?');
	}

	for (i = 0; i < s->ignored.nr; i++) {
		it = &(s->ignored.items[i]);
		wt_porcelain_v2_print_other(it, s, '!');
	}
}