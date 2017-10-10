	if (term_char != '\n' && term_char != EOF)
		ungetc(term_char, stdin);
}

static void parse_mark(void)
{
	if (starts_with(command_buf.buf, "mark :")) {
		next_mark = strtoumax(command_buf.buf + 6, NULL, 10);
		read_next_command();
	}
	else
		next_mark = 0;
}

static int parse_data(struct strbuf *sb, uintmax_t limit, uintmax_t *len_res)
{
	strbuf_reset(sb);

	if (!starts_with(command_buf.buf, "data "))
		die("Expected 'data n' command, found: %s", command_buf.buf);

	if (starts_with(command_buf.buf + 5, "<<")) {
		char *term = xstrdup(command_buf.buf + 5 + 2);
		size_t term_len = command_buf.len - 5 - 2;

		strbuf_detach(&command_buf, NULL);
		for (;;) {
			if (strbuf_getline(&command_buf, stdin, '\n') == EOF)
				die("EOF in data (terminator '%s' not found)", term);
			if (term_len == command_buf.len
