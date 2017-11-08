static void date_string(timestamp_t date, int offset, struct strbuf *buf)
{
	int sign = '+';

	if (offset < 0) {
		offset = -offset;
		sign = '-';
	}
	strbuf_addf(buf, "%"PRItime" %c%02d%02d", date, sign, offset / 60, offset % 60);
}