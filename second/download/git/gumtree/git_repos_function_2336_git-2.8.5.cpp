void perl_quote_buf(struct strbuf *sb, const char *src)
{
	const char sq = '\'';
	const char bq = '\\';
	char c;

	strbuf_addch(sb, sq);
	while ((c = *src++)) {
		if (c == sq || c == bq)
			strbuf_addch(sb, bq);
		strbuf_addch(sb, c);
	}
	strbuf_addch(sb, sq);
}