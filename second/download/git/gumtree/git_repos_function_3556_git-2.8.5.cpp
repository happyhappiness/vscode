int find_unique_abbrev_r(char *hex, const unsigned char *sha1, int len)
{
	int status, exists;

	sha1_to_hex_r(hex, sha1);
	if (len == 40 || !len)
		return 40;
	exists = has_sha1_file(sha1);
	while (len < 40) {
		unsigned char sha1_ret[20];
		status = get_short_sha1(hex, len, sha1_ret, GET_SHA1_QUIETLY);
		if (exists
		    ? !status
		    : status == SHORT_NAME_NOT_FOUND) {
			hex[len] = 0;
			return len;
		}
		len++;
	}
	return len;
}