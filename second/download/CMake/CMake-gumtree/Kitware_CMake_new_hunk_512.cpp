			return (0);
		if (bytes_read < 0)
			return (ARCHIVE_FATAL);
		nl = memchr(t, '\n', bytes_read);
		/* If we found '\n', trim the read to end exactly there. */
		if (nl != NULL) {
			bytes_read = ((const char *)nl) - ((const char *)t) + 1;
		}
		if (total_size + bytes_read + 1 > limit) {
			archive_set_error(&a->archive,
