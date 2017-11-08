static int parse_new_style_cacheinfo(const char *arg,
				     unsigned int *mode,
				     struct object_id *oid,
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
	if (get_oid_hex(endp, oid) || endp[GIT_SHA1_HEXSZ] != ',')
		return -1;
	*path = endp + GIT_SHA1_HEXSZ + 1;
	return 0;
}