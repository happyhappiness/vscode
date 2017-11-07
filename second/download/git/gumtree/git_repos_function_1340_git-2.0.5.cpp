static int date_string(unsigned long date, int offset, char *buf, int len)
{
	int sign = '+';

	if (offset < 0) {
		offset = -offset;
		sign = '-';
	}
	return snprintf(buf, len, "%lu %c%02d%02d", date, sign, offset / 60, offset % 60);
}