static void print_trace_line(struct trace_key *key, struct strbuf *buf)
{
	strbuf_complete_line(buf);
	trace_write(key, buf->buf, buf->len);
	strbuf_release(buf);
}