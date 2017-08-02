archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Too-small extra data: Need at least 4 bytes, but only found %d bytes", (int)extra_length)