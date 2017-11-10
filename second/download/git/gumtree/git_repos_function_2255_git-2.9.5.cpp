void strbuf_addbuf_percentquote(struct strbuf *dst, const struct strbuf *src)
{
	int i, len = src->len;

	for (i = 0; i < len; i++) {
		if (src->buf[i] == '%')
			strbuf_addch(dst, '%');
		strbuf_addch(dst, src->buf[i]);
	}
}