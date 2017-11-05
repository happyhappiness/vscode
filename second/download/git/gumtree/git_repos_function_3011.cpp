char *sha1_to_hex(const unsigned char *sha1)
{
	static int bufno;
	static char hexbuffer[4][GIT_SHA1_HEXSZ + 1];
	static const char hex[] = "0123456789abcdef";
	char *buffer = hexbuffer[3 & ++bufno], *buf = buffer;
	int i;

	for (i = 0; i < GIT_SHA1_RAWSZ; i++) {
		unsigned int val = *sha1++;
		*buf++ = hex[val >> 4];
		*buf++ = hex[val & 0xf];
	}
	*buf = '\0';

	return buffer;
}