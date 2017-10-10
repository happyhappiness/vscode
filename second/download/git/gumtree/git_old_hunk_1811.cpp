	else if (!strcmp(format, "raw"))
		return DATE_RAW;
	else
		die("unknown date format %s", format);
}

void datestamp(char *buf, int bufsize)
{
	time_t now;
	int offset;

	time(&now);

	offset = tm_to_time_t(localtime(&now)) - now;
	offset /= 60;

	date_string(now, offset, buf, bufsize);
}

/*
 * Relative time update (eg "2 days ago").  If we haven't set the time
 * yet, we need to set it from current time.
 */
