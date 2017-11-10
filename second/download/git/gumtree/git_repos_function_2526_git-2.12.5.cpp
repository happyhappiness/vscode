void strbuf_addftime(struct strbuf *sb, const char *fmt, const struct tm *tm)
{
	size_t hint = 128;
	size_t len;

	if (!*fmt)
		return;

	strbuf_grow(sb, hint);
	len = strftime(sb->buf + sb->len, sb->alloc - sb->len, fmt, tm);

	if (!len) {
		/*
		 * strftime reports "0" if it could not fit the result in the buffer.
		 * Unfortunately, it also reports "0" if the requested time string
		 * takes 0 bytes. So our strategy is to munge the format so that the
		 * output contains at least one character, and then drop the extra
		 * character before returning.
		 */
		struct strbuf munged_fmt = STRBUF_INIT;
		strbuf_addf(&munged_fmt, "%s ", fmt);
		while (!len) {
			hint *= 2;
			strbuf_grow(sb, hint);
			len = strftime(sb->buf + sb->len, sb->alloc - sb->len,
				       munged_fmt.buf, tm);
		}
		strbuf_release(&munged_fmt);
		len--; /* drop munged space */
	}
	strbuf_setlen(sb, sb->len + len);
}