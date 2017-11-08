static int verify_headers(const void *data, unsigned long size,
			  struct object *obj, fsck_error error_func)
{
	const char *buffer = (const char *)data;
	unsigned long i;

	for (i = 0; i < size; i++) {
		switch (buffer[i]) {
		case '\0':
			return error_func(obj, FSCK_ERROR,
				"unterminated header: NUL at offset %d", i);
		case '\n':
			if (i + 1 < size && buffer[i + 1] == '\n')
				return 0;
		}
	}

	/*
	 * We did not find double-LF that separates the header
	 * and the body.  Not having a body is not a crime but
	 * we do want to see the terminating LF for the last header
	 * line.
	 */
	if (size && buffer[size - 1] == '\n')
		return 0;

	return error_func(obj, FSCK_ERROR, "unterminated header");
}