int main(int argc, const char **argv)
{
	struct strbuf buf = STRBUF_INIT;
	int nongit;

	git_setup_gettext();

	git_extract_argv0_path(argv[0]);
	setup_git_directory_gently(&nongit);
	if (argc < 2) {
		error("remote-curl: usage: git remote-curl <remote> [<url>]");
		return 1;
	}

	options.verbosity = 1;
	options.progress = !!isatty(2);
	options.thin = 1;

	remote = remote_get(argv[1]);

	if (argc > 2) {
		end_url_with_slash(&url, argv[2]);
	} else {
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
			fflush(stdout);

		} else if (!strcmp(buf.buf, "capabilities")) {
			printf("fetch\n");
			printf("option\n");
			printf("push\n");
			printf("check-connectivity\n");
			printf("\n");
			fflush(stdout);
		} else {
			error("remote-curl: unknown command '%s' from git", buf.buf);
			return 1;
		}
		strbuf_reset(&buf);
	} while (1);

	http_cleanup();

	return 0;
}