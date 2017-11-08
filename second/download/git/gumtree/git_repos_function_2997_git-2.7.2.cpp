int get_sha1_hex(const char *hex, unsigned char *sha1)
{
	int i;
	for (i = 0; i < GIT_SHA1_RAWSZ; i++) {
		unsigned int val;
		/*
		 * hex[1]=='\0' is caught when val is checked below,
		 * but if hex[0] is NUL we have to avoid reading
		 * past the end of the string:
		 */
		if (!hex[0])
			return -1;
		val = (hexval(hex[0]) << 4) | hexval(hex[1]);
		if (val & ~0xff)
			return -1;
		*sha1++ = val;
		hex += 2;
	}
	return 0;
}