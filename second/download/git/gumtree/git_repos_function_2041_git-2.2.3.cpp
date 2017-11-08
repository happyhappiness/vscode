void python_quote_buf(struct strbuf *sb, const char *src)
{
	const char sq = '\'';
	const char bq = '\\';
	const char nl = '\n';
	char c;

	strbuf_addch(sb, sq);
	while ((c = *src++)) {
		if (c == nl) {
			strbuf_addch(sb, bq);
			strbuf_addch(sb, 'n');
			continue;
		}
		if (c == sq || c == bq)
			strbuf_addch(sb, bq);
		strbuf_addch(sb, c);
	}
	strbuf_addch(sb, sq);
}