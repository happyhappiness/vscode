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
				&& !strcmp(term, command_buf.buf))
				break;
			strbuf_addbuf(sb, &command_buf);
			strbuf_addch(sb, '\n');
		}
		free(term);
	}
	else {
		uintmax_t len = strtoumax(command_buf.buf + 5, NULL, 10);
		size_t n = 0, length = (size_t)len;

		if (limit && limit < len) {
			*len_res = len;
			return 0;
		}
		if (length < len)
			die("data is too large to use in this context");

		while (n < length) {
			size_t s = strbuf_fread(sb, length - n, stdin);
			if (!s && feof(stdin))
				die("EOF in data (%lu bytes remaining)",
					(unsigned long)(length - n));
			n += s;
		}
	}

	skip_optional_lf();
	return 1;
}