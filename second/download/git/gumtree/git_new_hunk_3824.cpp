		strbuf_addch(buf, ' ');
#endif

	return 1;
}

static void trace_write(struct trace_key *key, const void *buf, unsigned len)
{
	if (write_in_full(get_trace_fd(key), buf, len) < 0) {
		normalize_trace_key(&key);
		warning("unable to write trace for %s: %s",
			key->key, strerror(errno));
		trace_disable(key);
	}
}

void trace_verbatim(struct trace_key *key, const void *buf, unsigned len)
{
	if (!trace_want(key))
		return;
	trace_write(key, buf, len);
}

static void print_trace_line(struct trace_key *key, struct strbuf *buf)
{
	strbuf_complete_line(buf);
	trace_write(key, buf->buf, buf->len);
	strbuf_release(buf);
}

static void trace_vprintf_fl(const char *file, int line, struct trace_key *key,
			     const char *format, va_list ap)
{
