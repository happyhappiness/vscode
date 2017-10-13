static void wt_status_print_other(struct wt_status *s,
				  struct string_list *l,
				  const char *what,
				  const char *how)
{
	int i;
	struct strbuf buf = STRBUF_INIT;
	static struct string_list output = STRING_LIST_INIT_DUP;
	struct column_options copts;

	if (!l->nr)
		return;

	wt_status_print_other_header(s, what, how);

	for (i = 0; i < l->nr; i++) {
		struct string_list_item *it;
		const char *path;
		it = &(l->items[i]);
		path = quote_path(it->string, s->prefix, &buf);
		if (column_active(s->colopts)) {
			string_list_append(&output, path);
			continue;
		}
		status_printf(s, color(WT_STATUS_HEADER, s), "\t");
		status_printf_more(s, color(WT_STATUS_UNTRACKED, s),
				   "%s\n", path);
	}

	strbuf_release(&buf);
	if (!column_active(s->colopts))
		goto conclude;

	strbuf_addf(&buf, "%s%s\t%s",
		    color(WT_STATUS_HEADER, s),
		    s->display_comment_prefix ? "#" : "",
		    color(WT_STATUS_UNTRACKED, s));
	memset(&copts, 0, sizeof(copts));
	copts.padding = 1;
	copts.indent = buf.buf;
	if (want_color(s->use_color))
		copts.nl = GIT_COLOR_RESET "\n";
	print_columns(&output, s->colopts, &copts);
	string_list_clear(&output, 0);
	strbuf_release(&buf);
conclude:
	status_printf_ln(s, GIT_COLOR_NORMAL, "");
}