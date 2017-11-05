static char *parse_value(void)
{
	int quote = 0, comment = 0, space = 0;

	strbuf_reset(&cf->value);
	for (;;) {
		int c = get_next_char();
		if (c == '\n') {
			if (quote) {
				cf->linenr--;
				return NULL;
			}
			return cf->value.buf;
		}
		if (comment)
			continue;
		if (isspace(c) && !quote) {
			if (cf->value.len)
				space++;
			continue;
		}
		if (!quote) {
			if (c == ';' || c == '#') {
				comment = 1;
				continue;
			}
		}
		for (; space; space--)
			strbuf_addch(&cf->value, ' ');
		if (c == '\\') {
			c = get_next_char();
			switch (c) {
			case '\n':
				continue;
			case 't':
				c = '\t';
				break;
			case 'b':
				c = '\b';
				break;
			case 'n':
				c = '\n';
				break;
			/* Some characters escape as themselves */
			case '\\': case '"':
				break;
			/* Reject unknown escape sequences */
			default:
				return NULL;
			}
			strbuf_addch(&cf->value, c);
			continue;
		}
		if (c == '"') {
			quote = 1-quote;
			continue;
		}
		strbuf_addch(&cf->value, c);
	}
}