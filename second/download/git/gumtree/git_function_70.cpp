static const char *parse_arg(const char *next, struct strbuf *arg)
{
	/* Parse SP-terminated, possibly C-quoted argument */
	if (*next != '"')
		while (*next && !isspace(*next))
			strbuf_addch(arg, *next++);
	else if (unquote_c_style(arg, next, &next))
		die("badly quoted argument: %s", next);

	/* Return position after the argument */
	return next;
}