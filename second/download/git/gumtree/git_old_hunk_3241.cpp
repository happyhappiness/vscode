
	http_init(remote, url.buf, 0);

	do {
		const char *arg;

		if (strbuf_getline(&buf, stdin, '\n') == EOF) {
			if (ferror(stdin))
				error("remote-curl: error reading command stream from git");
			return 1;
		}
		if (buf.len == 0)
			break;
