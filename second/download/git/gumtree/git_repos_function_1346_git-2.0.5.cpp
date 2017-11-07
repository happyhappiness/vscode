void datestamp(char *buf, int bufsize)
{
	time_t now;
	int offset;

	time(&now);

	offset = tm_to_time_t(localtime(&now)) - now;
	offset /= 60;

	date_string(now, offset, buf, bufsize);
}