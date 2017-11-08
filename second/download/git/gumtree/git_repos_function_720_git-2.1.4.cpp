static void wt_status_print_unmerged_data(struct wt_status *s,
					  struct string_list_item *it)
{
	const char *c = color(WT_STATUS_UNMERGED, s);
	struct wt_status_change_data *d = it->util;
	struct strbuf onebuf = STRBUF_INIT;
	static char *padding;
	static int label_width;
	const char *one, *how;
	int len;

	if (!padding) {
		label_width = maxwidth(wt_status_unmerged_status_string, 1, 7);
		label_width += strlen(" ");
		padding = xmallocz(label_width);
		memset(padding, ' ', label_width);
	}

	one = quote_path(it->string, s->prefix, &onebuf);
	status_printf(s, color(WT_STATUS_HEADER, s), "\t");

	how = wt_status_unmerged_status_string(d->stagemask);
	len = label_width - utf8_strwidth(how);
	status_printf_more(s, c, "%s%.*s%s\n", how, len, padding, one);
	strbuf_release(&onebuf);
}