void strbuf_addftime(struct strbuf *sb, const char *fmt, const struct tm *tm,
		     int tz_offset, int suppress_tz_name)
{
	struct strbuf munged_fmt = STRBUF_INIT;
	size_t hint = 128;
	size_t len;

	if (!*fmt)
		return;

	/*
	 * There is no portable way to pass timezone information to
	 * strftime, so we handle %z and %Z here.
	 */
	for (;;) {
		const char *percent = strchrnul(fmt, '%');
		strbuf_add(&munged_fmt, fmt, percent - fmt);
		if (!*percent)
			break;
		fmt = percent + 1;
		switch (*fmt) {
		case '%':
			strbuf_addstr(&munged_fmt, "%%");
			fmt++;
			break;
		case 'z':
			strbuf_addf(&munged_fmt, "%+05d", tz_offset);
			fmt++;
			break;
		case 'Z':
			if (suppress_tz_name) {
				fmt++;
				break;
			}
			/* FALLTHROUGH */
		default:
			strbuf_addch(&munged_fmt, '%');
		}
	}
	fmt = munged_fmt.buf;

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
		strbuf_addch(&munged_fmt, ' ');
		while (!len) {
			hint *= 2;
			strbuf_grow(sb, hint);
			len = strftime(sb->buf + sb->len, sb->alloc - sb->len,
				       munged_fmt.buf, tm);
		}
		len--; /* drop munged space */
	}
	strbuf_release(&munged_fmt);
	strbuf_setlen(sb, sb->len + len);
}