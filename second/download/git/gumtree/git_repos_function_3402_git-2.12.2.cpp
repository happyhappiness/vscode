int get_sha1_hex(const char *hex, unsigned char *sha1)
{
	int i;
	for (i = 0; i < GIT_SHA1_RAWSZ; i++) {
		int val = hex2chr(hex);
		if (val < 0)
			return -1;
		*sha1++ = val;
		hex += 2;
	}
	return 0;
}