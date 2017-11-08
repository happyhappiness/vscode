static void append_lines(struct strbuf *out, const char *buf, unsigned long size, int lines)
{
	int i;
	const char *sp, *eol;
	size_t len;

	sp = buf;

	for (i = 0; i < lines && sp < buf + size; i++) {
		if (i)
			strbuf_addstr(out, "\n    ");
		eol = memchr(sp, '\n', size - (sp - buf));
		len = eol ? eol - sp : size - (sp - buf);
		strbuf_add(out, sp, len);
		if (!eol)
			break;
		sp = eol + 1;
	}
}