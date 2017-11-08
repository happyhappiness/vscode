static int url_decode_char(const char *q)
{
	int i;
	unsigned char val = 0;
	for (i = 0; i < 2; i++) {
		unsigned char c = *q++;
		val <<= 4;
		if (c >= '0' && c <= '9')
			val += c - '0';
		else if (c >= 'a' && c <= 'f')
			val += c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			val += c - 'A' + 10;
		else
			return -1;
	}
	return val;
}