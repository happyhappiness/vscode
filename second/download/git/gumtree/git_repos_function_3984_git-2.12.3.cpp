const char *find_unique_abbrev(const unsigned char *sha1, int len)
{
	static int bufno;
	static char hexbuffer[4][GIT_SHA1_HEXSZ + 1];
	char *hex = hexbuffer[bufno];
	bufno = (bufno + 1) % ARRAY_SIZE(hexbuffer);
	find_unique_abbrev_r(hex, sha1, len);
	return hex;
}