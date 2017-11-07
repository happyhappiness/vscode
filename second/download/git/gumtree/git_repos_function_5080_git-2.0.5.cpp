static const char *parse_first_arg(const char *next, struct strbuf *arg)
{
	/* Parse argument immediately after "command SP" */
	strbuf_reset(arg);
	if (line_termination) {
		/* Without -z, use the next argument */
		next = parse_arg(next, arg);
	} else {
		/* With -z, use rest of first NUL-terminated line */
		strbuf_addstr(arg, next);
		next = next + arg->len;
	}
	return next;
}