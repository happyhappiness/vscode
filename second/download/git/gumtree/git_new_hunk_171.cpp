	if (term_char != '\n' && term_char != EOF)
		ungetc(term_char, stdin);
}

static void parse_mark(void)
{
	const char *v;
	if (skip_prefix(command_buf.buf, "mark :", &v)) {
		next_mark = strtoumax(v, NULL, 10);
		read_next_command();
	}
	else
		next_mark = 0;
}

static int parse_data(struct strbuf *sb, uintmax_t limit, uintmax_t *len_res)
{
	const char *data;
	strbuf_reset(sb);

	if (!skip_prefix(command_buf.buf, "data ", &data))
		die("Expected 'data n' command, found: %s", command_buf.buf);

	if (skip_prefix(data, "<<", &data)) {
		char *term = xstrdup(data);
		size_t term_len = command_buf.len - (data - command_buf.buf);

		strbuf_detach(&command_buf, NULL);
		for (;;) {
			if (strbuf_getline(&command_buf, stdin, '\n') == EOF)
				die("EOF in data (terminator '%s' not found)", term);
			if (term_len == command_buf.len
