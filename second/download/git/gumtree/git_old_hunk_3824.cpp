		strbuf_addch(buf, ' ');
#endif

	return 1;
}

void trace_verbatim(struct trace_key *key, const void *buf, unsigned len)
{
	if (!trace_want(key))
		return;
	write_or_whine_pipe(get_trace_fd(key), buf, len, err_msg);
}

static void print_trace_line(struct trace_key *key, struct strbuf *buf)
{
	strbuf_complete_line(buf);

	write_or_whine_pipe(get_trace_fd(key), buf->buf, buf->len, err_msg);
	strbuf_release(buf);
}

static void trace_vprintf_fl(const char *file, int line, struct trace_key *key,
			     const char *format, va_list ap)
{
