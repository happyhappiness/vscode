void packet_flush(int fd)
{
	packet_trace("0000", 4, 1);
	write_or_die(fd, "0000", 4);
}

void packet_buf_flush(struct strbuf *buf)
{
	packet_trace("0000", 4, 1);
	strbuf_add(buf, "0000", 4);
}

#define hex(a) (hexchar[(a) & 15])
static void format_packet(struct strbuf *out, const char *fmt, va_list args)
{
	static char hexchar[] = "0123456789abcdef";
	size_t orig_len, n;

	orig_len = out->len;
	strbuf_addstr(out, "0000");
	strbuf_vaddf(out, fmt, args);
	n = out->len - orig_len;

	if (n > LARGE_PACKET_MAX)
		die("protocol error: impossibly long line");

	out->buf[orig_len + 0] = hex(n >> 12);
	out->buf[orig_len + 1] = hex(n >> 8);
	out->buf[orig_len + 2] = hex(n >> 4);
	out->buf[orig_len + 3] = hex(n);
	packet_trace(out->buf + orig_len + 4, n - 4, 1);
}

void packet_write(int fd, const char *fmt, ...)
{
	static struct strbuf buf = STRBUF_INIT;
	va_list args;

	strbuf_reset(&buf);
	va_start(args, fmt);
	format_packet(&buf, fmt, args);
	va_end(args);
	write_or_die(fd, buf.buf, buf.len);
}

void packet_buf_write(struct strbuf *buf, const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	format_packet(buf, fmt, args);
	va_end(args);
}

static int get_packet_data(int fd, char **src_buf, size_t *src_size,
			   void *dst, unsigned size, int options)
{
	ssize_t ret;

	if (fd >= 0 && src_buf && *src_buf)
