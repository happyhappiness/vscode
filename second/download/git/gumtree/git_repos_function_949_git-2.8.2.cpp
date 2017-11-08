void wt_shortstatus_print(struct wt_status *s)
{
	int i;

	if (s->show_branch)
		wt_shortstatus_print_tracking(s);

	for (i = 0; i < s->change.nr; i++) {
		struct wt_status_change_data *d;
		struct string_list_item *it;

		it = &(s->change.items[i]);
		d = it->util;
		if (d->stagemask)
			wt_shortstatus_unmerged(it, s);
		else
			wt_shortstatus_status(it, s);
	}
	for (i = 0; i < s->untracked.nr; i++) {
		struct string_list_item *it;

		it = &(s->untracked.items[i]);
		wt_shortstatus_other(it, s, "??");
	}
	for (i = 0; i < s->ignored.nr; i++) {
		struct string_list_item *it;

		it = &(s->ignored.items[i]);
		wt_shortstatus_other(it, s, "!!");
	}
}