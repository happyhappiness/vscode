static const char *quote_literal_for_format(const char *s)
{
	static struct strbuf buf = STRBUF_INIT;

	strbuf_reset(&buf);
	while (*s) {
		const char *ep = strchrnul(s, '%');
		if (s < ep)
			strbuf_add(&buf, s, ep - s);
		if (*ep == '%') {
			strbuf_addstr(&buf, "%%");
			s = ep + 1;
		} else {
			s = ep;
		}
	}
	return buf.buf;
}