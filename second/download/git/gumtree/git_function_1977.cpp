static enum date_mode_type parse_date_type(const char *format, const char **end)
{
	if (skip_prefix(format, "relative", end))
		return DATE_RELATIVE;
	if (skip_prefix(format, "iso8601-strict", end) ||
	    skip_prefix(format, "iso-strict", end))
		return DATE_ISO8601_STRICT;
	if (skip_prefix(format, "iso8601", end) ||
	    skip_prefix(format, "iso", end))
		return DATE_ISO8601;
	if (skip_prefix(format, "rfc2822", end) ||
	    skip_prefix(format, "rfc", end))
		return DATE_RFC2822;
	if (skip_prefix(format, "short", end))
		return DATE_SHORT;
	if (skip_prefix(format, "default", end))
		return DATE_NORMAL;
	if (skip_prefix(format, "raw", end))
		return DATE_RAW;
	if (skip_prefix(format, "format", end))
		return DATE_STRFTIME;

	die("unknown date format %s", format);
}