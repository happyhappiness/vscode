static void print_trace_line(struct trace_key *key, struct strbuf *buf)
{
	strbuf_complete_line(buf);

	write_or_whine_pipe(get_trace_fd(key), buf->buf, buf->len, err_msg);
	strbuf_release(buf);
}