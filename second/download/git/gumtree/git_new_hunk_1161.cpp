	string_list_clear(&output, 0);
	strbuf_release(&buf);
conclude:
	status_printf_ln(s, GIT_COLOR_NORMAL, "%s", "");
}

size_t wt_status_locate_end(const char *s, size_t len)
{
	const char *p;
	struct strbuf pattern = STRBUF_INIT;

	strbuf_addf(&pattern, "\n%c %s", comment_line_char, cut_line);
	if (starts_with(s, pattern.buf + 1))
		len = 0;
	else if ((p = strstr(s, pattern.buf)))
		len = p - s + 1;
	strbuf_release(&pattern);
	return len;
}

void wt_status_add_cut_line(FILE *fp)
{
	const char *explanation = _("Do not touch the line above.\nEverything below will be removed.");
	struct strbuf buf = STRBUF_INIT;
