static const char *parse_cmd_option(struct strbuf *input, const char *next)
{
	if (!strncmp(next, "no-deref", 8) && next[8] == line_termination)
		update_flags |= REF_NODEREF;
	else
		die("option unknown: %s", next);
	return next + 8;
}