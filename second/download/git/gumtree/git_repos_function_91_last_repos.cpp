static void add_rfc822_quoted(struct strbuf *out, const char *s, int len)
{
	int i;

	/* just a guess, we may have to also backslash-quote */
	strbuf_grow(out, len + 2);

	strbuf_addch(out, '"');
	for (i = 0; i < len; i++) {
		switch (s[i]) {
		case '"':
		case '\\':
			strbuf_addch(out, '\\');
			/* fall through */
		default:
			strbuf_addch(out, s[i]);
		}
	}
	strbuf_addch(out, '"');
}