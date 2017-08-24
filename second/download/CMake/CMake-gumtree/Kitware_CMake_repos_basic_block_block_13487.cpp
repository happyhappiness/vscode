(offset != extra_length) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Malformed extra data: Consumed %d bytes of %d bytes",
		    (int)offset, (int)extra_length);
		return ARCHIVE_FAILED;
	}