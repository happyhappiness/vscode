{
		if (total_size + bytes_read > limit) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Line too long");
			return (ARCHIVE_FATAL);
		}
		if (archive_string_ensure(&tar->line, total_size + bytes_read) == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate working buffer");
			return (ARCHIVE_FATAL);
		}
		memcpy(tar->line.s + total_size, t, bytes_read);
		tar_flush_unconsumed(a, unconsumed);
		total_size += bytes_read;
		/* If we found '\n', clean up and return. */
		if (p != NULL) {
			*start = tar->line.s;
			return (total_size);
		}
		/* Read some more. */
		t = __archive_read_ahead(a, 1, &bytes_read);
		if (bytes_read <= 0)
			return (ARCHIVE_FATAL);
		s = t;  /* Start of line? */
		p = memchr(t, '\n', bytes_read);
		/* If we found '\n', trim the read. */
		if (p != NULL) {
			bytes_read = 1 + ((const char *)p) - s;
		}
		*unconsumed = bytes_read;
	}