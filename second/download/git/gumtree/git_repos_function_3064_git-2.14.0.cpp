static void process_command_line_args(struct list_head *arg_head,
				      struct string_list *trailers)
{
	struct string_list_item *tr;
	struct arg_item *item;
	struct strbuf tok = STRBUF_INIT;
	struct strbuf val = STRBUF_INIT;
	const struct conf_info *conf;
	struct list_head *pos;

	/*
	 * In command-line arguments, '=' is accepted (in addition to the
	 * separators that are defined).
	 */
	char *cl_separators = xstrfmt("=%s", separators);

	/* Add an arg item for each configured trailer with a command */
	list_for_each(pos, &conf_head) {
		item = list_entry(pos, struct arg_item, list);
		if (item->conf.command)
			add_arg_item(arg_head,
				     xstrdup(token_from_item(item, NULL)),
				     xstrdup(""),
				     &item->conf);
	}

	/* Add an arg item for each trailer on the command line */
	for_each_string_list_item(tr, trailers) {
		int separator_pos = find_separator(tr->string, cl_separators);
		if (separator_pos == 0) {
			struct strbuf sb = STRBUF_INIT;
			strbuf_addstr(&sb, tr->string);
			strbuf_trim(&sb);
			error(_("empty trailer token in trailer '%.*s'"),
			      (int) sb.len, sb.buf);
			strbuf_release(&sb);
		} else {
			parse_trailer(&tok, &val, &conf, tr->string,
				      separator_pos);
			add_arg_item(arg_head,
				     strbuf_detach(&tok, NULL),
				     strbuf_detach(&val, NULL),
				     conf);
		}
	}

	free(cl_separators);
}