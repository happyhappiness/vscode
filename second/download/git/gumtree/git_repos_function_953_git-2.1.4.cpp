void end_url_with_slash(struct strbuf *buf, const char *url)
{
	strbuf_addstr(buf, url);
	if (buf->len && buf->buf[buf->len - 1] != '/')
		strbuf_addch(buf, '/');
}