timestamp_t approxidate_relative(const char *date, const struct timeval *tv)
{
	timestamp_t timestamp;
	int offset;
	int errors = 0;

	if (!parse_date_basic(date, &timestamp, &offset))
		return timestamp;
	return approxidate_str(date, tv, &errors);
}