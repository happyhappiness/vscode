static void print_trace_line(struct trace_key *key, struct strbuf *buf)
{
	/* append newline if missing */
	if (buf->len && buf->buf[buf->len - 1] != '\n')
		strbuf_addch(buf, '\n');

	write_or_whine_pipe(get_trace_fd(key), buf->buf, buf->len, err_msg);
	strbuf_release(buf);
}