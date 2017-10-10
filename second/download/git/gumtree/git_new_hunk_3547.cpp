	if (skip_prefix(format, "short", end))
		return DATE_SHORT;
	if (skip_prefix(format, "default", end))
		return DATE_NORMAL;
	if (skip_prefix(format, "raw", end))
		return DATE_RAW;
	if (skip_prefix(format, "unix", end))
		return DATE_UNIX;
	if (skip_prefix(format, "format", end))
		return DATE_STRFTIME;

	die("unknown date format %s", format);
}

