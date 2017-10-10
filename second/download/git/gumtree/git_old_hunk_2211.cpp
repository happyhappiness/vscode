		state.refresh_cache = 0;
	}

	/* Check out named files first */
	for (i = 0; i < argc; i++) {
		const char *arg = argv[i];
		const char *p;

		if (all)
			die("git checkout-index: don't mix '--all' and explicit filenames");
		if (read_from_stdin)
			die("git checkout-index: don't mix '--stdin' and explicit filenames");
		p = prefix_path(prefix, prefix_length, arg);
		checkout_file(p, prefix);
		if (p < arg || p > arg + strlen(arg))
			free((char *)p);
	}

	if (read_from_stdin) {
		struct strbuf buf = STRBUF_INIT, nbuf = STRBUF_INIT;

		if (all)
			die("git checkout-index: don't mix '--all' and '--stdin'");

		while (strbuf_getline(&buf, stdin, line_termination) != EOF) {
			const char *p;
			if (line_termination && buf.buf[0] == '"') {
				strbuf_reset(&nbuf);
				if (unquote_c_style(&nbuf, buf.buf, NULL))
					die("line is badly quoted");
				strbuf_swap(&buf, &nbuf);
			}
			p = prefix_path(prefix, prefix_length, buf.buf);
			checkout_file(p, prefix);
			if (p < buf.buf || p > buf.buf + buf.len)
				free((char *)p);
		}
		strbuf_release(&nbuf);
		strbuf_release(&buf);
	}

	if (all)
