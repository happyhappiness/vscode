	string_list_clear(&output, 0);
	strbuf_release(&buf);
conclude:
	status_printf_ln(s, GIT_COLOR_NORMAL, "%s", "");
}

void wt_status_truncate_message_at_cut_line(struct strbuf *buf)
{
	const char *p;
	struct strbuf pattern = STRBUF_INIT;

	strbuf_addf(&pattern, "\n%c %s", comment_line_char, cut_line);
	if (starts_with(buf->buf, pattern.buf + 1))
		strbuf_setlen(buf, 0);
	else if ((p = strstr(buf->buf, pattern.buf)))
		strbuf_setlen(buf, p - buf->buf + 1);
	strbuf_release(&pattern);
}

void wt_status_add_cut_line(FILE *fp)
{
	const char *explanation = _("Do not touch the line above.\nEverything below will be removed.");
	struct strbuf buf = STRBUF_INIT;
