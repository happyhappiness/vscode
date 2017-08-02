archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Malformed attribute \"%s\" (%d)", key, key[0])