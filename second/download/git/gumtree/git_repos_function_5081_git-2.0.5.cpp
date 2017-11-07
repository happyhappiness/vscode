static const char *parse_next_arg(const char *next, struct strbuf *arg)
{
	/* Parse next SP-terminated or NUL-terminated argument, if any */
	strbuf_reset(arg);
	if (line_termination) {
		/* Without -z, consume SP and use next argument */
		if (!*next)
			return NULL;
		if (*next != ' ')
			die("expected SP but got: %s", next);
		next = parse_arg(next + 1, arg);
	} else {
		/* With -z, read the next NUL-terminated line */
		if (*next)
			die("expected NUL but got: %s", next);
		if (strbuf_getline(arg, stdin, '\0') == EOF)
			return NULL;
		next = arg->buf + arg->len;
	}
	return next;
}