void datestamp(struct strbuf *out)
{
	time_t now;
	int offset;

	time(&now);

	offset = tm_to_time_t(localtime(&now)) - now;
	offset /= 60;

	date_string(now, offset, out);
}