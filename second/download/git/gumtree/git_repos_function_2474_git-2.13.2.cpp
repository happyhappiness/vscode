static int read_one_header_line(struct strbuf *line, FILE *in)
{
	struct strbuf continuation = STRBUF_INIT;

	/* Get the first part of the line. */
	if (strbuf_getline_lf(line, in))
		return 0;

	/*
	 * Is it an empty line or not a valid rfc2822 header?
	 * If so, stop here, and return false ("not a header")
	 */
	strbuf_rtrim(line);
	if (!line->len || !is_rfc2822_header(line)) {
		/* Re-add the newline */
		strbuf_addch(line, '\n');
		return 0;
	}

	/*
	 * Now we need to eat all the continuation lines..
	 * Yuck, 2822 header "folding"
	 */
	for (;;) {
		int peek;

		peek = fgetc(in);
		if (peek == EOF)
			break;
		ungetc(peek, in);
		if (peek != ' ' && peek != '\t')
			break;
		if (strbuf_getline_lf(&continuation, in))
			break;
		continuation.buf[0] = ' ';
		strbuf_rtrim(&continuation);
		strbuf_addbuf(line, &continuation);
	}
	strbuf_release(&continuation);

	return 1;
}