static int parse_sha1_header_extended(const char *hdr, struct object_info *oi,
			       unsigned int flags)
{
	const char *type_buf = hdr;
	unsigned long size;
	int type, type_len = 0;

	/*
	 * The type can be of any size but is followed by
	 * a space.
	 */
	for (;;) {
		char c = *hdr++;
		if (c == ' ')
			break;
		type_len++;
	}

	type = type_from_string_gently(type_buf, type_len, 1);
	if (oi->typename)
		strbuf_add(oi->typename, type_buf, type_len);
	/*
	 * Set type to 0 if its an unknown object and
	 * we're obtaining the type using '--allow-unkown-type'
	 * option.
	 */
	if ((flags & LOOKUP_UNKNOWN_OBJECT) && (type < 0))
		type = 0;
	else if (type < 0)
		die("invalid object type");
	if (oi->typep)
		*oi->typep = type;

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

	if (oi->sizep)
		*oi->sizep = size;

	/*
	 * The length must be followed by a zero byte
	 */
	return *hdr ? -1 : type;
}