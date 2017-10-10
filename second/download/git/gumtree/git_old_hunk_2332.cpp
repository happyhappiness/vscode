
/*
 * We used to just use "sscanf()", but that's actually way
 * too permissive for what we want to check. So do an anal
 * object header parse by hand.
 */
int parse_sha1_header(const char *hdr, unsigned long *sizep)
{
	char type[10];
	int i;
	unsigned long size;

	/*
	 * The type can be at most ten bytes (including the
	 * terminating '\0' that we add), and is followed by
	 * a space.
	 */
	i = 0;
	for (;;) {
		char c = *hdr++;
		if (c == ' ')
			break;
		type[i++] = c;
		if (i >= sizeof(type))
			return -1;
	}
	type[i] = 0;

	/*
	 * The length must follow immediately, and be in canonical
	 * decimal format (ie "010" is not valid).
	 */
	size = *hdr++ - '0';
