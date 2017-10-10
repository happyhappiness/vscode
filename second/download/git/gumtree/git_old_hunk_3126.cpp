	free(full_path);
}

static void check_attr_stdin_paths(const char *prefix, int cnt,
	struct git_attr_check *check)
{
	struct strbuf buf, nbuf;
	int line_termination = nul_term_line ? 0 : '\n';

	strbuf_init(&buf, 0);
	strbuf_init(&nbuf, 0);
	while (strbuf_getline(&buf, stdin, line_termination) != EOF) {
		if (line_termination && buf.buf[0] == '"') {
			strbuf_reset(&nbuf);
			if (unquote_c_style(&nbuf, buf.buf, NULL))
				die("line is badly quoted");
			strbuf_swap(&buf, &nbuf);
		}
		check_attr(prefix, cnt, check, buf.buf);
		maybe_flush_or_die(stdout, "attribute to stdout");
	}
	strbuf_release(&buf);
	strbuf_release(&nbuf);
}

static NORETURN void error_with_usage(const char *msg)
{
	error("%s", msg);
	usage_with_options(check_attr_usage, check_attr_options);
