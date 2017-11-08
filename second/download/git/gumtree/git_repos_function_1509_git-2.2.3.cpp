static int require_end_of_header(const void *data, unsigned long size,
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

	return error_func(obj, FSCK_ERROR, "unterminated header");
}