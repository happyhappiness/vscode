static void wt_status_print_unmerged(struct wt_status *s)
{
	int shown_header = 0;
	int i;

	for (i = 0; i < s->change.nr; i++) {
		struct wt_status_change_data *d;
		struct string_list_item *it;
		it = &(s->change.items[i]);
		d = it->util;
		if (!d->stagemask)
			continue;
		if (!shown_header) {
			wt_status_print_unmerged_header(s);
			shown_header = 1;
		}
		wt_status_print_unmerged_data(s, it);
	}
	if (shown_header)
		wt_status_print_trailer(s);

}