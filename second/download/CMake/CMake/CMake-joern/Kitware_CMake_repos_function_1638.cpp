static int
cab_skip_sfx(struct archive_read *a)
{
	const char *p, *q;
	size_t skip;
	ssize_t bytes, window;

	window = 4096;
	for (;;) {
		const char *h = __archive_read_ahead(a, window, &bytes);
		if (h == NULL) {
			/* Remaining size are less than window. */
			window >>= 1;
			if (window < 128) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Couldn't find out CAB header");
				return (ARCHIVE_FATAL);
			}
			continue;
		}
		p = h;
		q = p + bytes;

		/*
		 * Scan ahead until we find something that looks
		 * like the cab header.
		 */
		while (p + 8 < q) {
			int next;
			if ((next = find_cab_magic(p)) == 0) {
				skip = p - h;
				__archive_read_consume(a, skip);
				return (ARCHIVE_OK);
			}
			p += next;
		}
		skip = p - h;
		__archive_read_consume(a, skip);
	}
}