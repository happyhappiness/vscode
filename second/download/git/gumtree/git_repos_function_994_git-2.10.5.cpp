void strbuf_utf8_align(struct strbuf *buf, align_type position, unsigned int width,
		       const char *s)
{
	int slen = strlen(s);
	int display_len = utf8_strnwidth(s, slen, 0);
	int utf8_compensation = slen - display_len;

	if (display_len >= width) {
		strbuf_addstr(buf, s);
		return;
	}

	if (position == ALIGN_LEFT)
		strbuf_addf(buf, "%-*s", width + utf8_compensation, s);
	else if (position == ALIGN_MIDDLE) {
		int left = (width - display_len) / 2;
		strbuf_addf(buf, "%*s%-*s", left, "", width - left + utf8_compensation, s);
	} else if (position == ALIGN_RIGHT)
		strbuf_addf(buf, "%*s", width + utf8_compensation, s);
}