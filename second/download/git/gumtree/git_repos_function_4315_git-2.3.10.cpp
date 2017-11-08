static int parseopt_dump(const struct option *o, const char *arg, int unset)
{
	struct strbuf *parsed = o->value;
	if (unset)
		strbuf_addf(parsed, " --no-%s", o->long_name);
	else if (o->short_name && (o->long_name == NULL || !stuck_long))
		strbuf_addf(parsed, " -%c", o->short_name);
	else
		strbuf_addf(parsed, " --%s", o->long_name);
	if (arg) {
		if (!stuck_long)
			strbuf_addch(parsed, ' ');
		else if (o->long_name)
			strbuf_addch(parsed, '=');
		sq_quote_buf(parsed, arg);
	}
	return 0;
}