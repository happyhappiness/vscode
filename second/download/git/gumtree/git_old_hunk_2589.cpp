	if (parse_date_basic(date, &timestamp, &offset))
		return -1;
	date_string(timestamp, offset, result);
	return 0;
}

enum date_mode parse_date_format(const char *format)
{
	if (!strcmp(format, "relative"))
		return DATE_RELATIVE;
	else if (!strcmp(format, "iso8601") ||
		 !strcmp(format, "iso"))
		return DATE_ISO8601;
	else if (!strcmp(format, "iso8601-strict") ||
		 !strcmp(format, "iso-strict"))
		return DATE_ISO8601_STRICT;
	else if (!strcmp(format, "rfc2822") ||
		 !strcmp(format, "rfc"))
		return DATE_RFC2822;
	else if (!strcmp(format, "short"))
		return DATE_SHORT;
	else if (!strcmp(format, "local"))
		return DATE_LOCAL;
	else if (!strcmp(format, "default"))
		return DATE_NORMAL;
	else if (!strcmp(format, "raw"))
		return DATE_RAW;
	else
		die("unknown date format %s", format);
}

void datestamp(struct strbuf *out)
{
	time_t now;
