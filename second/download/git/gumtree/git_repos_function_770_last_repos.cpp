static void format_packet(struct strbuf *out, const char *fmt, va_list args)
{
	size_t orig_len, n;

	orig_len = out->len;
	strbuf_addstr(out, "0000");
	strbuf_vaddf(out, fmt, args);
	n = out->len - orig_len;

	if (n > LARGE_PACKET_MAX)
		die("protocol error: impossibly long line");

	set_packet_header(&out->buf[orig_len], n);
	packet_trace(out->buf + orig_len + 4, n - 4, 1);
}