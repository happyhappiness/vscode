(memcmp(p, _7ZIP_SIGNATURE, 6) != 0) {
		archive_set_error(&a->archive, -1, "Not 7-Zip archive file");
		return (ARCHIVE_FATAL);
	}