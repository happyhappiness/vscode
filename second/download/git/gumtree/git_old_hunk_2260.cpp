
	if (read_from_stdin) {
		struct strbuf buf = STRBUF_INIT, nbuf = STRBUF_INIT;

		setup_work_tree();
		while (strbuf_getline(&buf, stdin, line_termination) != EOF) {
			const char *p;
			if (line_termination && buf.buf[0] == '"') {
				strbuf_reset(&nbuf);
				if (unquote_c_style(&nbuf, buf.buf, NULL))
					die("line is badly quoted");
				strbuf_swap(&buf, &nbuf);
			}
			p = prefix_path(prefix, prefix_length, buf.buf);
			update_one(p);
			if (set_executable_bit)
				chmod_path(set_executable_bit, p);
			free((char *)p);
		}
		strbuf_release(&nbuf);
		strbuf_release(&buf);
	}

	if (split_index > 0) {
