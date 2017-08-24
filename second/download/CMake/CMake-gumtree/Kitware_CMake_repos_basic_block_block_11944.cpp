(header_crc != lha->header_crc) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "LHa header CRC error");
		return (ARCHIVE_FATAL);
	}