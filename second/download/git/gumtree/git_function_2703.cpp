static void wt_status_print_change_data(struct wt_status *s,
					int change_type,
					struct string_list_item *it)
{
	struct wt_status_change_data *d = it->util;
	const char *c = color(change_type, s);
	int status;
	char *one_name;
	char *two_name;
	const char *one, *two;
	struct strbuf onebuf = STRBUF_INIT, twobuf = STRBUF_INIT;
	struct strbuf extra = STRBUF_INIT;
	static char *padding;
	static int label_width;
	const char *what;
	int len;

	if (!padding) {
		/* If DIFF_STATUS_* uses outside the range [A..Z], we're in trouble */
		label_width = maxwidth(wt_status_diff_status_string, 'A', 'Z');
		label_width += strlen(" ");
		padding = xmallocz(label_width);
		memset(padding, ' ', label_width);
	}

	one_name = two_name = it->string;
	switch (change_type) {
	case WT_STATUS_UPDATED:
		status = d->index_status;
		if (d->head_path)
			one_name = d->head_path;
		break;
	case WT_STATUS_CHANGED:
		if (d->new_submodule_commits || d->dirty_submodule) {
			strbuf_addstr(&extra, " (");
			if (d->new_submodule_commits)
				strbuf_addf(&extra, _("new commits, "));
			if (d->dirty_submodule & DIRTY_SUBMODULE_MODIFIED)
				strbuf_addf(&extra, _("modified content, "));
			if (d->dirty_submodule & DIRTY_SUBMODULE_UNTRACKED)
				strbuf_addf(&extra, _("untracked content, "));
			strbuf_setlen(&extra, extra.len - 2);
			strbuf_addch(&extra, ')');
		}
		status = d->worktree_status;
		break;
	default:
		die("BUG: unhandled change_type %d in wt_status_print_change_data",
		    change_type);
	}

	one = quote_path(one_name, s->prefix, &onebuf);
	two = quote_path(two_name, s->prefix, &twobuf);

	status_printf(s, color(WT_STATUS_HEADER, s), "\t");
	what = wt_status_diff_status_string(status);
	if (!what)
		die(_("bug: unhandled diff status %c"), status);
	len = label_width - utf8_strwidth(what);
	assert(len >= 0);
	if (status == DIFF_STATUS_COPIED || status == DIFF_STATUS_RENAMED)
		status_printf_more(s, c, "%s%.*s%s -> %s",
				   what, len, padding, one, two);
	else
		status_printf_more(s, c, "%s%.*s%s",
				   what, len, padding, one);
	if (extra.len) {
		status_printf_more(s, color(WT_STATUS_HEADER, s), "%s", extra.buf);
		strbuf_release(&extra);
	}
	status_printf_more(s, GIT_COLOR_NORMAL, "\n");
	strbuf_release(&onebuf);
	strbuf_release(&twobuf);
}