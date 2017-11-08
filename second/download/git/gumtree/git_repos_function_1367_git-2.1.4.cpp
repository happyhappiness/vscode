int parse_date(const char *date, char *result, int maxlen)
{
	unsigned long timestamp;
	int offset;
	if (parse_date_basic(date, &timestamp, &offset))
		return -1;
	return date_string(timestamp, offset, result, maxlen);
}