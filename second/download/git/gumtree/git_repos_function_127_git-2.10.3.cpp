void pp_remainder(struct pretty_print_context *pp,
		  const char **msg_p,
		  struct strbuf *sb,
		  int indent)
{
	int first = 1;
	for (;;) {
		const char *line = *msg_p;
		int linelen = get_one_line(line);
		*msg_p += linelen;

		if (!linelen)
			break;

		if (is_blank_line(line, &linelen)) {
			if (first)
				continue;
			if (pp->fmt == CMIT_FMT_SHORT)
				break;
		}
		first = 0;

		strbuf_grow(sb, linelen + indent + 20);
		if (indent)
			pp_handle_indent(pp, sb, indent, line, linelen);
		else if (pp->expand_tabs_in_log)
			strbuf_add_tabexpand(sb, pp->expand_tabs_in_log,
					     line, linelen);
		else {
			if (pp->fmt == CMIT_FMT_MBOXRD &&
					is_mboxrd_from(line, linelen))
				strbuf_addch(sb, '>');

			strbuf_add(sb, line, linelen);
		}
		strbuf_addch(sb, '\n');
	}
}