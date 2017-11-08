const char *find_unique_abbrev(const unsigned char *sha1, int len)
{
	static char hex[GIT_SHA1_HEXSZ + 1];
	find_unique_abbrev_r(hex, sha1, len);
	return hex;
}