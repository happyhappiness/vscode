		end_url_with_slash(&url, remote->url[0]);
	}

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
		if (starts_with(buf.buf, "fetch ")) {
			if (nongit)
				die("remote-curl: fetch attempted without a local repo");
			parse_fetch(&buf);

		} else if (!strcmp(buf.buf, "list") || starts_with(buf.buf, "list ")) {
			int for_push = !!strstr(buf.buf + 4, "for-push");
			output_refs(get_refs(for_push));

		} else if (starts_with(buf.buf, "push ")) {
			parse_push(&buf);

		} else if (skip_prefix(buf.buf, "option ", &arg)) {
			char *value = strchr(arg, ' ');
			int result;

			if (value)
				*value++ = '\0';
			else
				value = "true";

			result = set_option(arg, value);
			if (!result)
				printf("ok\n");
			else if (result < 0)
				printf("error invalid value\n");
			else
				printf("unsupported\n");
