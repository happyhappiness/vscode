const char *sum_as_hex(const char *sum)
{
	static char buf[MAX_DIGEST_LEN*2+1];
	int i, x1, x2;
	char *c = buf + checksum_len*2;

	assert(c - buf < (int)sizeof buf);

	*c = '\0';

	for (i = checksum_len; --i >= 0; ) {
		x1 = CVAL(sum, i);
		x2 = x1 >> 4;
		x1 &= 0xF;
		*--c = x1 <= 9 ? x1 + '0' : x1 + 'a' - 10;
		*--c = x2 <= 9 ? x2 + '0' : x2 + 'a' - 10;
	}

	return buf;
}