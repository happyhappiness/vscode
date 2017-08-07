{
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unsupported header version(%d)",
		    archive_be16dec(b+6));
		return (ARCHIVE_FATAL);
	}