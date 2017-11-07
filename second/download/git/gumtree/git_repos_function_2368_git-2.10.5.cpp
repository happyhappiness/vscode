void sq_quotef(struct strbuf *dst, const char *fmt, ...)
{
	struct strbuf src = STRBUF_INIT;

	va_list ap;
	va_start(ap, fmt);
	strbuf_vaddf(&src, fmt, ap);
	va_end(ap);

	sq_quote_buf(dst, src.buf);
	strbuf_release(&src);
}