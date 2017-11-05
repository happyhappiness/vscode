void parse_date_format(const char *format, struct date_mode *mode)
{
	const char *p;

	/* historical alias */
	if (!strcmp(format, "local"))
		format = "default-local";

	mode->type = parse_date_type(format, &p);
	mode->local = 0;

	if (skip_prefix(p, "-local", &p))
		mode->local = 1;

	if (mode->type == DATE_STRFTIME) {
		if (!skip_prefix(p, ":", &p))
			die("date format missing colon separator: %s", format);
		mode->strftime_fmt = xstrdup(p);
	} else if (*p)
		die("unknown date format %s", format);
}