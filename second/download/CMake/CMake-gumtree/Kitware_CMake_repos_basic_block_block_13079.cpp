(archive_be32dec(b) != HEADER_MAGIC) {
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Invalid header magic");
		return (ARCHIVE_FATAL);
	}