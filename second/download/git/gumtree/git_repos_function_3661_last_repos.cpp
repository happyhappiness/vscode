char *sha1_to_hex(const unsigned char *sha1)
{
	static int bufno;
	static char hexbuffer[4][GIT_MAX_HEXSZ + 1];
	bufno = (bufno + 1) % ARRAY_SIZE(hexbuffer);
	return sha1_to_hex_r(hexbuffer[bufno], sha1);
}