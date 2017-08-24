(p != NULL) {
		bytes_read = 1 + ((const char *)p) - s;
		if (bytes_read > limit) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Line too long");
			return (ARCHIVE_FATAL);
		}
		*unconsumed = bytes_read;
		*start = s;
		return (bytes_read);
	}