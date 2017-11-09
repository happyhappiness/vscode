void strbuf_addf(struct strbuf *sb, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	strbuf_vaddf(sb, fmt, ap);
	va_end(ap);
}