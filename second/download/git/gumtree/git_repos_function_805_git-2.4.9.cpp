static void wt_shortstatus_unmerged(struct string_list_item *it,
			   struct wt_status *s)
{
	struct wt_status_change_data *d = it->util;
	const char *how = "??";

	switch (d->stagemask) {
	case 1: how = "DD"; break; /* both deleted */
	case 2: how = "AU"; break; /* added by us */
	case 3: how = "UD"; break; /* deleted by them */
	case 4: how = "UA"; break; /* added by them */
	case 5: how = "DU"; break; /* deleted by us */
	case 6: how = "AA"; break; /* both added */
	case 7: how = "UU"; break; /* both modified */
	}
	color_fprintf(s->fp, color(WT_STATUS_UNMERGED, s), "%s", how);
	if (s->null_termination) {
		fprintf(stdout, " %s%c", it->string, 0);
	} else {
		struct strbuf onebuf = STRBUF_INIT;
		const char *one;
		one = quote_path(it->string, s->prefix, &onebuf);
		printf(" %s\n", one);
		strbuf_release(&onebuf);
	}
}