static int get_base_var(struct strbuf *name)
{
	for (;;) {
		int c = get_next_char();
		if (cf->eof)
			return -1;
		if (c == ']')
			return 0;
		if (isspace(c))
			return get_extended_base_var(name, c);
		if (!iskeychar(c) && c != '.')
			return -1;
		strbuf_addch(name, tolower(c));
	}
}