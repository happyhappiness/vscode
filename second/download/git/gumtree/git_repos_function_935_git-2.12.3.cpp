static void status_vprintf(struct wt_status *s, int at_bol, const char *color,
		const char *fmt, va_list ap, const char *trail)
{
	struct strbuf sb = STRBUF_INIT;
	struct strbuf linebuf = STRBUF_INIT;
	const char *line, *eol;

	strbuf_vaddf(&sb, fmt, ap);
	if (!sb.len) {
		if (s->display_comment_prefix) {
			strbuf_addch(&sb, comment_line_char);
			if (!trail)
				strbuf_addch(&sb, ' ');
		}
		color_print_strbuf(s->fp, color, &sb);
		if (trail)
			fprintf(s->fp, "%s", trail);
		strbuf_release(&sb);
		return;
	}
	for (line = sb.buf; *line; line = eol + 1) {
		eol = strchr(line, '\n');

		strbuf_reset(&linebuf);
		if (at_bol && s->display_comment_prefix) {
			strbuf_addch(&linebuf, comment_line_char);
			if (*line != '\n' && *line != '\t')
				strbuf_addch(&linebuf, ' ');
		}
		if (eol)
			strbuf_add(&linebuf, line, eol - line);
		else
			strbuf_addstr(&linebuf, line);
		color_print_strbuf(s->fp, color, &linebuf);
		if (eol)
			fprintf(s->fp, "\n");
		else
			break;
		at_bol = 1;
	}
	if (trail)
		fprintf(s->fp, "%s", trail);
	strbuf_release(&linebuf);
	strbuf_release(&sb);
}