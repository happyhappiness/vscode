(stat(path, &st) != 0) {
		archive_set_error(&(a->archive), errno, "Failed to stat()");
		return (ARCHIVE_FAILED);
	}