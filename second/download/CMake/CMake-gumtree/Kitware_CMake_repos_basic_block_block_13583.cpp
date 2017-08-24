(bytes_avail < 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated ZIP file body");
		return (ARCHIVE_FATAL);
	}