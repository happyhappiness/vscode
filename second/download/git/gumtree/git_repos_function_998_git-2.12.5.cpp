static void wt_porcelain_v2_print_changed_entry(
	struct string_list_item *it,
	struct wt_status *s)
{
	struct wt_status_change_data *d = it->util;
	struct strbuf buf_index = STRBUF_INIT;
	struct strbuf buf_head = STRBUF_INIT;
	const char *path_index = NULL;
	const char *path_head = NULL;
	char key[3];
	char submodule_token[5];
	char sep_char, eol_char;

	wt_porcelain_v2_fix_up_changed(it, s);
	wt_porcelain_v2_submodule_state(d, submodule_token);

	key[0] = d->index_status ? d->index_status : '.';
	key[1] = d->worktree_status ? d->worktree_status : '.';
	key[2] = 0;

	if (s->null_termination) {
		/*
		 * In -z mode, we DO NOT C-quote pathnames.  Current path is ALWAYS first.
		 * A single NUL character separates them.
		 */
		sep_char = '\0';
		eol_char = '\0';
		path_index = it->string;
		path_head = d->head_path;
	} else {
		/*
		 * Path(s) are C-quoted if necessary. Current path is ALWAYS first.
		 * The source path is only present when necessary.
		 * A single TAB separates them (because paths can contain spaces
		 * which are not escaped and C-quoting does escape TAB characters).
		 */
		sep_char = '\t';
		eol_char = '\n';
		path_index = quote_path(it->string, s->prefix, &buf_index);
		if (d->head_path)
			path_head = quote_path(d->head_path, s->prefix, &buf_head);
	}

	if (path_head)
		fprintf(s->fp, "2 %s %s %06o %06o %06o %s %s %c%d %s%c%s%c",
				key, submodule_token,
				d->mode_head, d->mode_index, d->mode_worktree,
				oid_to_hex(&d->oid_head), oid_to_hex(&d->oid_index),
				key[0], d->score,
				path_index, sep_char, path_head, eol_char);
	else
		fprintf(s->fp, "1 %s %s %06o %06o %06o %s %s %s%c",
				key, submodule_token,
				d->mode_head, d->mode_index, d->mode_worktree,
				oid_to_hex(&d->oid_head), oid_to_hex(&d->oid_index),
				path_index, eol_char);

	strbuf_release(&buf_index);
	strbuf_release(&buf_head);
}