			return (0);
		if (bytes_read < 0)
			return (ARCHIVE_FATAL);
		s = t;  /* Start of line? */
		p = memchr(t, '\n', bytes_read);
		/* If we found '\n', trim the read. */
		if (p != NULL) {
			bytes_read = 1 + ((const char *)p) - s;
		}
		if (total_size + bytes_read + 1 > limit) {
			archive_set_error(&a->archive,
