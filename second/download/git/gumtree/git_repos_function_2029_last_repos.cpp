timestamp_t approxidate_careful(const char *date, int *error_ret)
{
	struct timeval tv;
	timestamp_t timestamp;
	int offset;
	int dummy = 0;
	if (!error_ret)
		error_ret = &dummy;

	if (!parse_date_basic(date, &timestamp, &offset)) {
		*error_ret = 0;
		return timestamp;
	}

	gettimeofday(&tv, NULL);
	return approxidate_str(date, &tv, error_ret);
}