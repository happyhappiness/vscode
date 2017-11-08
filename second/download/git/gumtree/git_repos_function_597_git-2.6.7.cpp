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