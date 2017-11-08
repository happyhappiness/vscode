static void add_path(struct strbuf *buf, size_t base_len, const char *path)
{
	strbuf_setlen(buf, base_len);
	if (buf->len && buf->buf[buf->len - 1] != '/')
		strbuf_addch(buf, '/');
	strbuf_addstr(buf, path);
}