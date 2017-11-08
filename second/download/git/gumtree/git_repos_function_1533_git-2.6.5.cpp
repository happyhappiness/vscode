static void date_string(unsigned long date, int offset, struct strbuf *buf)
{
	int sign = '+';

	if (offset < 0) {
		offset = -offset;
		sign = '-';
	}
	strbuf_addf(buf, "%lu %c%02d%02d", date, sign, offset / 60, offset % 60);
}