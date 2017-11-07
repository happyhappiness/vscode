static int get_extended_base_var(struct strbuf *name, int c)
{
	do {
		if (c == '\n')
			goto error_incomplete_line;
		c = get_next_char();
	} while (isspace(c));

	/* We require the format to be '[base "extension"]' */
	if (c != '"')
		return -1;
	strbuf_addch(name, '.');

	for (;;) {
		int c = get_next_char();
		if (c == '\n')
			goto error_incomplete_line;
		if (c == '"')
			break;
		if (c == '\\') {
			c = get_next_char();
			if (c == '\n')
				goto error_incomplete_line;
		}
		strbuf_addch(name, c);
	}

	/* Final ']' */
	if (get_next_char() != ']')
		return -1;
	return 0;
error_incomplete_line:
	cf->linenr--;
	return -1;
}