	__archive_read_consume(a, 4);

	/*return (ARCHIVE_OK);
	 * This is not fully implemnted yet.*/
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "Encrypted file is unsupported");
	return (ARCHIVE_FAILED);
