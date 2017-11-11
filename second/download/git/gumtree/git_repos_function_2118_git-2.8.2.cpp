static struct strbuf *decode_q_segment(const struct strbuf *q_seg, int rfc2047)
{
	const char *in = q_seg->buf;
	int c;
	struct strbuf *out = xmalloc(sizeof(struct strbuf));
	strbuf_init(out, q_seg->len);

	while ((c = *in++) != 0) {
		if (c == '=') {
			int d = *in++;
			if (d == '\n' || !d)
				break; /* drop trailing newline */
			strbuf_addch(out, (hexval(d) << 4) | hexval(*in++));
			continue;
		}
		if (rfc2047 && c == '_') /* rfc2047 4.2 (2) */
			c = 0x20;
		strbuf_addch(out, c);
	}
	return out;
}