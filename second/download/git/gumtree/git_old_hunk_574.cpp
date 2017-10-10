	}

	fputs(summary.buf, s->fp);
	strbuf_release(&summary);
}

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
