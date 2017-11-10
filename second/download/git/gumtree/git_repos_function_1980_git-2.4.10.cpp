void strbuf_vaddf(struct strbuf *sb, const char *fmt, va_list ap)
{
	int len;
	va_list cp;

	if (!strbuf_avail(sb))
		strbuf_grow(sb, 64);
	va_copy(cp, ap);
	len = vsnprintf(sb->buf + sb->len, sb->alloc - sb->len, fmt, cp);
	va_end(cp);
	if (len < 0)
		die("BUG: your vsnprintf is broken (returned %d)", len);
	if (len > strbuf_avail(sb)) {
		strbuf_grow(sb, len);
		len = vsnprintf(sb->buf + sb->len, sb->alloc - sb->len, fmt, ap);
		if (len > strbuf_avail(sb))
			die("BUG: your vsnprintf is broken (insatiable)");
	}
	strbuf_setlen(sb, sb->len + len);
}