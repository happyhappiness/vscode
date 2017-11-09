static int parse_opt_signed_tag_mode(const struct option *opt,
				     const char *arg, int unset)
{
	if (unset || !strcmp(arg, "abort"))
		signed_tag_mode = ABORT;
	else if (!strcmp(arg, "verbatim") || !strcmp(arg, "ignore"))
		signed_tag_mode = VERBATIM;
	else if (!strcmp(arg, "warn"))
		signed_tag_mode = WARN;
	else if (!strcmp(arg, "warn-strip"))
		signed_tag_mode = WARN_STRIP;
	else if (!strcmp(arg, "strip"))
		signed_tag_mode = STRIP;
	else
		return error("Unknown signed-tags mode: %s", arg);
	return 0;
}