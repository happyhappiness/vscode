(lha_check_header_format(p) != 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Bad LHa file");
		return (ARCHIVE_FATAL);
	}