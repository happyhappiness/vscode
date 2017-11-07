void wt_status_truncate_message_at_cut_line(struct strbuf *buf)
{
	const char *p;
	struct strbuf pattern = STRBUF_INIT;

	strbuf_addf(&pattern, "%c %s", comment_line_char, cut_line);
	p = strstr(buf->buf, pattern.buf);
	if (p && (p == buf->buf || p[-1] == '\n'))
		strbuf_setlen(buf, p - buf->buf);
	strbuf_release(&pattern);
}