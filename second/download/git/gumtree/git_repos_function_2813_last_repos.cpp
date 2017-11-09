void basic_regex_quote_buf(struct strbuf *sb, const char *src)
{
	char c;

	if (*src == '^') {
		/* only beginning '^' is special and needs quoting */
		strbuf_addch(sb, '\\');
		strbuf_addch(sb, *src++);
	}
	if (*src == '*')
		/* beginning '*' is not special, no quoting */
		strbuf_addch(sb, *src++);

	while ((c = *src++)) {
		switch (c) {
		case '[':
		case '.':
		case '\\':
		case '*':
			strbuf_addch(sb, '\\');
			strbuf_addch(sb, c);
			break;

		case '$':
			/* only the end '$' is special and needs quoting */
			if (*src == '\0')
				strbuf_addch(sb, '\\');
			strbuf_addch(sb, c);
			break;

		default:
			strbuf_addch(sb, c);
			break;
		}
	}
}