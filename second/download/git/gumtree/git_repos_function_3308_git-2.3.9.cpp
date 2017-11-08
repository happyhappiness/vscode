static int get_describe_name(const char *name, int len, unsigned char *sha1)
{
	const char *cp;
	unsigned flags = GET_SHA1_QUIETLY | GET_SHA1_COMMIT;

	for (cp = name + len - 1; name + 2 <= cp; cp--) {
		char ch = *cp;
		if (!isxdigit(ch)) {
			/* We must be looking at g in "SOMETHING-g"
			 * for it to be describe output.
			 */
			if (ch == 'g' && cp[-1] == '-') {
				cp++;
				len -= cp - name;
				return get_short_sha1(cp, len, sha1, flags);
			}
		}
	}
	return -1;
}