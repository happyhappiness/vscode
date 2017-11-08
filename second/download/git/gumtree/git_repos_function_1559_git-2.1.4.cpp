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
	if (size > 9)
		return -1;
	if (size) {
		for (;;) {
			unsigned long c = *hdr - '0';
			if (c > 9)
				break;
			hdr++;
			size = size * 10 + c;
		}
	}
	*sizep = size;

	/*
	 * The length must be followed by a zero byte
	 */
	return *hdr ? -1 : type_from_string(type);
}