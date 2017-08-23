	    && bytes_avail > zip->entry_bytes_remaining) {
		bytes_avail = (ssize_t)zip->entry_bytes_remaining;
	}
	if (bytes_avail <= 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated ZIP file body");
		return (ARCHIVE_FATAL);
