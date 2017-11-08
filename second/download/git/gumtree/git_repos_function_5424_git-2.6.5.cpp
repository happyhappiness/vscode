static int parse_new_style_cacheinfo(const char *arg,
				     unsigned int *mode,
				     unsigned char sha1[],
				     const char **path)
{
	unsigned long ul;
	char *endp;

	if (!arg)
		return -1;

	errno = 0;
	ul = strtoul(arg, &endp, 8);
	if (errno || endp == arg || *endp != ',' || (unsigned int) ul != ul)
		return -1; /* not a new-style cacheinfo */
	*mode = ul;
	endp++;
	if (get_sha1_hex(endp, sha1) || endp[40] != ',')
		return -1;
	*path = endp + 41;
	return 0;
}