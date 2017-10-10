	if (skip_prefix(data, "<<", &data)) {
		char *term = xstrdup(data);
		size_t term_len = command_buf.len - (data - command_buf.buf);

		strbuf_detach(&command_buf, NULL);
		for (;;) {
			if (strbuf_getline_lf(&command_buf, stdin) == EOF)
				die("EOF in data (terminator '%s' not found)", term);
			if (term_len == command_buf.len
				&& !strcmp(term, command_buf.buf))
				break;
			strbuf_addbuf(sb, &command_buf);
			strbuf_addch(sb, '\n');
