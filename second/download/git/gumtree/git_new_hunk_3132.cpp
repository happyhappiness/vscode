		p = prefix_path(prefix, prefix_length, arg);
		checkout_file(p, prefix);
		free(p);
	}

	if (read_from_stdin) {
		struct strbuf buf = STRBUF_INIT;
		struct strbuf unquoted = STRBUF_INIT;
		strbuf_getline_fn getline_fn;

		if (all)
			die("git checkout-index: don't mix '--all' and '--stdin'");

		getline_fn = nul_term_line ? strbuf_getline_nul : strbuf_getline_lf;
		while (getline_fn(&buf, stdin) != EOF) {
			char *p;
			if (!nul_term_line && buf.buf[0] == '"') {
				strbuf_reset(&unquoted);
				if (unquote_c_style(&unquoted, buf.buf, NULL))
					die("line is badly quoted");
				strbuf_swap(&buf, &unquoted);
			}
			p = prefix_path(prefix, prefix_length, buf.buf);
			checkout_file(p, prefix);
			free(p);
		}
		strbuf_release(&unquoted);
		strbuf_release(&buf);
	}

	if (all)
		checkout_all(prefix, prefix_length);

