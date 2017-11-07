void trace_strbuf(const char *key, const struct strbuf *buf)
{
	int fd, need_close = 0;

	fd = get_trace_fd(key, &need_close);
	if (!fd)
		return;

	write_or_whine_pipe(fd, buf->buf, buf->len, err_msg);

	if (need_close)
		close(fd);
}