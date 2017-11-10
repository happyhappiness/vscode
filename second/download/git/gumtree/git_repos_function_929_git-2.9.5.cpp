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