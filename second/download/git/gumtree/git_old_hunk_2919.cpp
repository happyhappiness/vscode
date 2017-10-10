	if (parse_date_basic(date, &timestamp, &offset))
		return -1;
	date_string(timestamp, offset, result);
	return 0;
}

void parse_date_format(const char *format, struct date_mode *mode)
{
	if (!strcmp(format, "relative"))
		mode->type = DATE_RELATIVE;
	else if (!strcmp(format, "iso8601") ||
		 !strcmp(format, "iso"))
		mode->type = DATE_ISO8601;
	else if (!strcmp(format, "iso8601-strict") ||
		 !strcmp(format, "iso-strict"))
		mode->type = DATE_ISO8601_STRICT;
	else if (!strcmp(format, "rfc2822") ||
		 !strcmp(format, "rfc"))
		mode->type = DATE_RFC2822;
	else if (!strcmp(format, "short"))
		mode->type = DATE_SHORT;
	else if (!strcmp(format, "local"))
		mode->type = DATE_LOCAL;
	else if (!strcmp(format, "default"))
		mode->type = DATE_NORMAL;
	else if (!strcmp(format, "raw"))
		mode->type = DATE_RAW;
	else if (skip_prefix(format, "format:", &format)) {
		mode->type = DATE_STRFTIME;
		mode->strftime_fmt = xstrdup(format);
	} else
		die("unknown date format %s", format);
}

void datestamp(struct strbuf *out)
{
	time_t now;
