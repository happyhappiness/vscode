	compressed_buff = __archive_read_ahead(a, 1, &bytes_avail);
	if (0 == (zip->entry->flags & ZIP_LENGTH_AT_END)
	    && bytes_avail > zip->entry_bytes_remaining) {
		bytes_avail = (ssize_t)zip->entry_bytes_remaining;
	}
	if (bytes_avail <= 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
