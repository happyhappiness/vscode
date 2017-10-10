
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
