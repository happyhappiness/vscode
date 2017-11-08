static const char *parse_arg(const char *next, struct strbuf *arg)
{
	if (*next == '"') {
		const char *orig = next;

		if (unquote_c_style(arg, next, &next))
			die("badly quoted argument: %s", orig);
		if (*next && !isspace(*next))
			die("unexpected character after quoted argument: %s", orig);
	} else {
		while (*next && !isspace(*next))
			strbuf_addch(arg, *next++);
	}

	return next;
}