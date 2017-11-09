static void wt_shortstatus_print(struct wt_status *s)
{
	struct string_list_item *it;

	if (s->show_branch)
		wt_shortstatus_print_tracking(s);

	for_each_string_list_item(it, &s->change) {
		struct wt_status_change_data *d = it->util;

		if (d->stagemask)
			wt_shortstatus_unmerged(it, s);
		else
			wt_shortstatus_status(it, s);
	}
	for_each_string_list_item(it, &s->untracked)
		wt_shortstatus_other(it, s, "??");

	for_each_string_list_item(it, &s->ignored)
		wt_shortstatus_other(it, s, "!!");
}